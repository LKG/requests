#include "https.h"

BinaryData https_get(const string &url){
	LPCTSTR lpszAgent = L"WinInetGet/0.1";
	//��ʼ��
	HINTERNET hInternet = InternetOpen(lpszAgent,
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	LPCTSTR lpszServerName = L"www.cnblogs.com";//"ssl.google-analytics.com"; //����server
	INTERNET_PORT nServerPort = INTERNET_DEFAULT_HTTPS_PORT; // HTTPS�˿�443
	LPCTSTR lpszUserName = NULL; //�޵�¼�û���
	LPCTSTR lpszPassword = NULL; //�޵�¼����
	DWORD dwConnectFlags = 0;
	DWORD dwConnectContext = 0;
	//����
	HINTERNET hConnect = InternetConnect(hInternet,
		lpszServerName, nServerPort,
		lpszUserName, lpszPassword,
		INTERNET_SERVICE_HTTP,
		dwConnectFlags, dwConnectContext);
	//ʹ��Get
	LPCTSTR lpszVerb = L"GET";
	LPCTSTR lpszObjectName = L"/jetyi/articles/2740802.html";
	LPCTSTR lpszVersion = L"HTTP/1.1";    // Ĭ��.
	LPCTSTR lpszReferrer = NULL;   // û������ҳ
	LPCTSTR *lplpszAcceptTypes = NULL; // Accpet��������.
	DWORD dwOpenRequestFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
		INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTH |
		INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_UI |
		//��������HTTPS
		INTERNET_FLAG_SECURE |
		INTERNET_FLAG_RELOAD;
	DWORD dwOpenRequestContext = 0;
	//��ʼ��Request
	HINTERNET hRequest = HttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion,
		lpszReferrer, lplpszAcceptTypes,
		dwOpenRequestFlags, dwOpenRequestContext);
	//����Request
again:
	DWORD dwError = 0;
	if (!HttpSendRequest(hRequest, NULL, 0, NULL, 0))
	{
		dwError = GetLastError();
	}
	if (dwError == ERROR_INTERNET_INVALID_CA)
	{
		fprintf(stderr, "HttpSendRequest failed, error = %d (0x%x)/n",
			dwError, dwError);

		DWORD dwFlags;
		DWORD dwBuffLen = sizeof(dwFlags);
		InternetQueryOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS,
			(LPVOID)&dwFlags, &dwBuffLen);

		dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
		InternetSetOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS,
			&dwFlags, sizeof(dwFlags));
		goto again;
	}

	//���HTTP Response Header��Ϣ
	DWORD dwInfoLevel = HTTP_QUERY_RAW_HEADERS_CRLF;
	DWORD dwInfoBufferLength = 2048;
	BYTE *pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength + 2);
	while (!HttpQueryInfo(hRequest, dwInfoLevel, pInfoBuffer, &dwInfoBufferLength, NULL)) {
		DWORD dwError = GetLastError();
		if (dwError == ERROR_INSUFFICIENT_BUFFER) {
			free(pInfoBuffer);
			pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength + 2);
		}
		else {
			fprintf(stderr, "HttpQueryInfo failed, error = %d (0x%x)/n",
				GetLastError(), GetLastError());
			break;
		}
	}
	pInfoBuffer[dwInfoBufferLength] = '/0';
	pInfoBuffer[dwInfoBufferLength + 1] = '/0';
	printf("Header:%S", pInfoBuffer); //�����HttpQueryInfo����ĸ�ʽ��wchar_t �������InternetReadFile��һ��
	free(pInfoBuffer);
	//HTTP Response �� Body, ��Ҫ�����ݾ�������
	DWORD dwBytesAvailable;
	BYTE *pMessageBody = NULL;
	BinaryData content(1000);
	while (InternetQueryDataAvailable(hRequest, &dwBytesAvailable, 0, 0)) {
		pMessageBody = (BYTE *)malloc(dwBytesAvailable + 1);
		DWORD dwBytesRead;
		BOOL bResult = InternetReadFile(hRequest, pMessageBody,
			dwBytesAvailable, &dwBytesRead);
		if (!bResult) {
			fprintf(stderr, "InternetReadFile failed, error = %d (0x%x)/n",
				GetLastError(), GetLastError());
			break;
		}
		if (dwBytesRead == 0)
			break; // End of File.
		printf("fill data%d",dwBytesRead);
		content.append(pMessageBody, dwBytesRead);
	}
	free(pMessageBody);
	return content;
}
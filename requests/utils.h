#ifndef utils996
#define utils996
#include <string>
#include <algorithm>
#include <Windows.h>//

std::wstring s2ws(const std::string& str);
std::string  ws2s(const std::wstring &str);
std::string to_lower(std::string str);

class Base64
{
public:
	/*����
	DataByte
	[in]��������ݳ���,���ֽ�Ϊ��λ
	*/
	std::string Encode(const unsigned char* Data, int DataByte);
	/*����
	DataByte
	[in]��������ݳ���,���ֽ�Ϊ��λ
	OutByte
	[out]��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����
	������ݵĳ���
	*/
	std::string Decode(const char* Data, int DataByte, int& OutByte);
};
#endif
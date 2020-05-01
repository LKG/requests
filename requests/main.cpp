// requests.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include "http.h"
using	namespace std;
using	namespace requests;

string generate_key(string &name){
	string info = "{\"openid\":\"oIaII0UXKpdR7x1r901Jz9ipIFzA\",\"key\":\"%s\",\"page\":1,\"timestamp\":%d}";
	char	buffer[200] = { 0 };
	time_t	t = time(0);
	sprintf_s(buffer, 200, info.c_str(), name.c_str(), t);
	Base64 b64;
	return b64.Encode(buffer, strlen(buffer));
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	map<string, string> header;
	map<string, string> options;
	map<string, string> data;
	map<string, string> files;
	int a;
	options["timeout"] = "3000";
	data["key"] = "letmeupload";
	data["submit"] = "Submit";
	files["file"] = "C:\\Users\\jack\\Desktop\\key.txt";
	try{
		Response resp = Post("http://httpbin.org/post", "name=lx&age=24",header,"",options);
		cout << resp.status << endl;
		cout << resp.GetText() << endl;
	}
	catch (const char *msg){
		cout << msg << endl;
	}

	cin >> a;
	return 0;
}


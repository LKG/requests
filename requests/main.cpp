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
	int a=0;
	stringstream info;
	string name = "2016212073";
	string url = "http://47.106.162.182:8080/post.php";//"https://we.cqu.pt/api/get_student_info.php";
	//cout << "�������ֻ���ѧ��:";
	//cin >> name;
	string key = generate_key(name);
	data["name"] = key;
	data["age"] = "14";
	Response html = Post(url,data);
	cout << html.status << endl;
	cout << html.GetText() << endl;
		/*CJsonObject json(html.GetText());
		json.Get("status", a);
		if (a == 200){
			info << "����:" << json["data"]["rows"][0]("xm") << "\n";
			info << "��������:" << json["data"]["rows"][0]("csrq") << "\n";
			info << "ѧ��:" << json["data"]["rows"][0]("xh") << "\n";
			info << "ѧԺ:" << json["data"]["rows"][0]("yxm") << "\n";
			info << "רҵ:" << json["data"]["rows"][0]("zymEn") << "\n";
			info << "��ѧʱ��:" << json["data"]["rows"][0]("nj") << "\n";
			info << "״̬:" << json["data"]["rows"][0]("xjzt") << "\n";
			info << "�༶����:" << json["data"]["rows"][0]("bj") << "\n";
			cout << info.str();
		}*/
	cin >> a;
	return 0;
}


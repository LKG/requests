// requests.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "http.h"
using	namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	
	BinaryData	bd;
	bd.append("name=lxe&age=14");
	int a;
	Response rep = https_post("http://47.106.162.182/post.php",bd);
	cout << rep["kkk"] << endl;
	cout << rep.GetText() << endl;
	cout << "-----------------------" << endl;
	/*cout << "---------HTTPS----------" << endl;
	Response bin = https_get("https://img12.360buyimg.com/n1/s450x450_jfs/t1/48975/24/16741/337144/5de0913eE206334a5/32c2af4c117024c3.jpg");
	header = bin.Header();
	cout << "File size: " << bin.size() << endl;
	cout << bin["status"] << endl;
	fstream png("baidu.jpg", ios::out | ios::binary);
	png.write((const char*)bin.GetBinary(), bin.size());
	png.close();*/
	cin >> a;
	return 0;
}


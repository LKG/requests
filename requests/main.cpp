// requests.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "http.h"
using	namespace std;


int _tmain(int argc, _TCHAR* argv[])
{

	
	int a;
	Response rep = Get("http://47.106.162.182/112358.php");
	cout << rep["status"] << endl;
	cout << rep.GetText() << endl;
	cin >> a;
	return 0;
}


#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
class Response
{
public:
	Response();
	explicit Response(string &rep);
	~Response();
	string	GetText()const;
	string	operator[](string key);
private:
	map<string, string>	header;
	string	text;
	void SplitString(const string& s, vector<string>& v, const string& c);
};

class Request
{
public:
	Request(std::string url,const map<string, string> &header);
	~Request();
	string	HeaderToString();
	std::string	url;
	std::string	domain;
	std::string param;
	map<string, string>	header;
	int	port;
};

std::string GetIpByDomainName(const char *szHost);
Response	Get(std::string url, const map<string,string> &head = map<string,string>());
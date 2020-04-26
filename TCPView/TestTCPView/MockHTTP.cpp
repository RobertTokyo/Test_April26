#include "MockHTTP.h"
#include <vector>

/*
0;;;WRONG INPUT
|
+ your request has not been processed due to invalid syntax
	|
	+ e.g. bad IPv4 like 300.400.abc.256
	+ e.g. bad decimal like 2a3b4c or bigger than MAX_INT


1;CD;COD;COUNTRY
|
+ contains two-letter (ISO 3166) and three-letter country codes, and a full country name
+ country name may be multi-word and contain spaces
+ e.g. we take your IP:
	|
	+ URL looks like this:  https://ip2c.org/62.232.247.219
	|                       or
	|                       https://ip2c.org/?ip=62.232.247.219
	|
	+ resulting string is:  1;GB;GBR;United Kingdom


2;;;UNKNOWN
|
+ given ip/dec not found in database or not yet physically assigned to any country


*/

const std::vector<std::string> cmds { std::string{ "0" }, std::string{ "1;GB;GBR;United Kingdom" }, std::string{ "2" } };
size_t INDEX{ 0 };
std::string MockHTTP::get(const std::string& url)
{
	if (INDEX == cmds.size())
		INDEX = 0;

	return cmds[INDEX++];
}

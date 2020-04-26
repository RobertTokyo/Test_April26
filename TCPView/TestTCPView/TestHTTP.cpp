#include "pch.h"
#include "CppUnitTest.h"
#include "TCPReport.h"
#include "MockHTTP.h"
#include "URL.h"
#include "CommandHTTP.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr char* msg = "12:07:02.131014 IP rtsg.1023 > csam.login: Flags [S], seq 768512:768512, win 4096, opts [mss 1024]";

namespace TestTCPView
{
	TEST_CLASS(TestHTTP)
	{
	public:

		TEST_METHOD(MockHTTP_Responses)
		{
			MockHTTP http;
			std::string res = http.get("");
			Assert::IsTrue(strcmp("0", res.c_str()) == 0);
			
			res = http.get("");
			Assert::IsTrue(strcmp("1;GB;GBR;United Kingdom", res.c_str()) == 0);
			
			res = http.get("");
			Assert::IsTrue(strcmp("2", res.c_str()) == 0);
		}

		TEST_METHOD(URL_ParseURL)
		{
			URL myURL("http://myhost.domain.com:80/index.html");
			Assert::IsTrue(strcmp("myhost.domain.com", myURL.getHost().c_str()) == 0);
		}

		TEST_METHOD(URL_ParseSampleReq)
		{
			URL myURL("https://ip2c.org/62.232.247.219");
			Assert::IsTrue(strcmp("ip2c.org", myURL.getHost().c_str()) == 0);
			Assert::IsTrue(strcmp("62.232.247.219", myURL.getReqPath().c_str()) == 0);
		}

		TEST_METHOD(Command_Fetch)
		{
			// DANGER!!!
			CommandHTTP myCmd("https://ip2c.org/62.232.247.219");
			std::string rep = myCmd.get();
			Assert::IsTrue(strcmp("1;GB;GBR;United Kingdom", rep.c_str()) == 0);
		}

		TEST_METHOD(Command_FetchDQ)
		{
			// DANGER!!!
			CommandHTTP myCmd("https://77.55.235.217/62.232.247.219");
			std::string rep = myCmd.get();
			Assert::IsTrue(strcmp("1;GB;GBR;United Kingdom", rep.c_str()) == 0);
		}
	};
}

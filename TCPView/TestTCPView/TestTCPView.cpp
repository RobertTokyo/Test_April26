#include "pch.h"
#include "CppUnitTest.h"
#include "TCPReport.h"
#include "MockHTTP.h"
#include <chrono>
#include <ctime>
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr char* msg = "12:07:02.131014 IP rtsg.1023 > csam.login: Flags [S], seq 768512:768512, win 4096, opts [mss 1024]";

namespace TestTCPView
{
	TEST_CLASS(TestTCPView)
	{
	public:
		
		TEST_METHOD(TCPReport_SrcHost)
		{
			TCPReport report;
			bool parsed = report.parse(msg, 3);
			Assert::IsTrue(parsed);
			if(parsed)
			{
				std::string src = report.getSrc();
				Assert::IsTrue(src.length() > 0);
				Assert::IsTrue(strcmp("rtsg", src.c_str())==0);
			}
		}

		TEST_METHOD(TCPReport_DestHost)
		{
			TCPReport report;
			bool parsed = report.parse(msg, 5);
			Assert::IsTrue(parsed);
			if (parsed)
			{
				std::string dest = report.getDest();
				Assert::IsTrue(dest.length() > 0);
				Assert::IsTrue(strcmp("csam.login:", dest.c_str())==0);
			}
		}

		TEST_METHOD(TCPReport_Timestamp)
		{
			TCPReport report;
			bool parsed = report.parse(msg, 1);
			Assert::IsTrue(parsed);
			if (parsed)
			{
				std::string ts = report.getTimestamp();
				Assert::IsTrue(ts.length() > 0);

				std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				std::tm* local = std::localtime(&now);
				std::stringstream ss;
				std::array<std::string, 12> months{ "January", "February", "March", "April", "May", "June",
								"July", "August", "September", "October", "November", "Decemeber" };
				ss << local->tm_mday << ' ' << months[local->tm_mon] << ' ' << local->tm_year + 1900;
				ss << ", 12:07";
				Assert::IsTrue(strcmp(ss.str().c_str(), ts.c_str())==0);
			}
		}

		TEST_METHOD(TCPReport_Location)
		{
			// This mock return 0, 1, 2 as location result (and repeats)
			MockHTTP http;
			LocationResolver locn(&http, "77.55.235.219");
			TCPReport report(&locn);
			bool parsed = report.parse(msg, 5);
			Assert::IsTrue(parsed);
			if (parsed)
			{
				std::string locn = report.getLocation();
				Assert::IsTrue(locn.length() > 0);
				Assert::IsTrue(strcmp("Error", locn.c_str())==0);
			}
			parsed = report.parse(msg, 5);
			Assert::IsTrue(parsed);
			if (parsed)
			{
				std::string locn = report.getLocation();
				Assert::IsTrue(locn.length() > 0);
				Assert::IsTrue(strcmp("United Kingdom", locn.c_str()) == 0);
			}
			parsed = report.parse(msg, 5);
			Assert::IsTrue(parsed);
			if (parsed)
			{
				std::string locn = report.getLocation();
				Assert::IsTrue(locn.length() > 0);
				Assert::IsTrue(strcmp("Unknown", locn.c_str()) == 0);
			}
		}

	};
}

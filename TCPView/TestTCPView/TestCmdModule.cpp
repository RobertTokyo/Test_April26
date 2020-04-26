#include "CppUnitTest.h"
#include "SysCommand.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr char* msg = "12:07:02.131014 IP rtsg.1023 > csam.login: Flags [S], seq 768512:768512, win 4096, opts [mss 1024]";

namespace TestTCPView
{
	TEST_CLASS(TestHTTP)
	{
	public:

		TEST_METHOD(SysCommand_1)
		{
			SysCommand cmd;

			std::string res = cmd.execute("dir");
		}
	};
}

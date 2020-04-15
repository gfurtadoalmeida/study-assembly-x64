#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_struct.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::Struct;
using namespace Assembly::Core::Types;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(Struct)
			{
			public:
				TEST_METHOD(Test_Get_CPU_Info)
				{
					const ProcessorInfo cpu = ProcessorInfo();

					Assert::IsTrue(Get_CPU_Info(&cpu));
					Assert::IsNotNull(cpu.Name);
					Assert::IsNotNull(cpu.Vendor);

					Logger::WriteMessage(&cpu.Name[0]);
					Logger::WriteMessage(&cpu.Vendor[0]);
				}
			};
		}
	}
}
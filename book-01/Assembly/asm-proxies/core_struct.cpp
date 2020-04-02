#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_struct.h"

namespace Assembly {
	namespace Core {
		namespace Struct {

			bool Get_CPU_Info(const ProcessorInfo* processorInfo)
			{
				return Core_Struct_Get_CPU_Info_(processorInfo);
			}
		}
	}
}

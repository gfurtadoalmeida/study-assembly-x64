#pragma once
#include "types_core.h"

using namespace Assembly::Core::Types;

namespace Assembly {
	namespace Core {
		namespace Struct {

			__declspec(dllexport) int Get_CPU_Info(const ProcessorInfo* processorInfo);
		}
	}
}

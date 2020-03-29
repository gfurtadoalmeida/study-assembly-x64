#pragma once

#include <cstdint>
#include "types_avx.h"

using namespace Assembly::AVX::Types;

namespace Assembly {
	namespace AVX {
		namespace Scalar {

			__declspec(dllexport) double Calc_Euclidian_Distance(double x1, double y1, double z1, double x2, double y2, double z2);
			__declspec(dllexport) bool Calc_Mean_Stdev(const double* values, int arrayLength, double* mean, double* stdev);
			__declspec(dllexport) void Calc_Sphere_Area_Volume(double radius, double* area, double* volume);
			__declspec(dllexport) int Compare_Double_VCMPSD(double a, double b);
			__declspec(dllexport) int Compare_Double_VCOMISD(double a, double b);
			__declspec(dllexport) float Convert_Celsius_Fahrenheit(float degree);
			__declspec(dllexport) float Convert_Fahrenheit_Celsius(float degree);
			__declspec(dllexport) bool Convert_Number(const Uval* source, const Uval* destination, CvtOp operation);
		}
	}
}
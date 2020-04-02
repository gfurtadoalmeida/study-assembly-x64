#pragma once

#include <cstdint>
#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx_scalar.h"

namespace Assembly {
	namespace AVX {
		namespace Scalar {

			double Calc_Euclidian_Distance(double x1, double y1, double z1, double x2, double y2, double z2)
			{
				return AVX_Scalar_Calc_Euclidian_Distance_(x1, y1, z1, x2, y2, z2);
			}

			bool Calc_Mean_Stdev(const double* values, uint32_t arrayLength, double* mean, double* stdev)
			{
				return AVX_Scalar_Calc_Mean_Stdev_(values, arrayLength, mean, stdev);
			}

			void Calc_Sphere_Area_Volume(double radius, double* area, double* volume)
			{
				AVX_Scalar_Calc_Sphere_Area_Volume_(radius, area, volume);
			}

			int32_t Compare_VCOMISD_Double(double a, double b)
			{
				return AVX_Scalar_Compare_VCOMISD_Double_(a, b);
			}

			int32_t Compare_VCMPSD_Double(double a, double b)
			{
				return AVX_Scalar_Compare_VCMPSD_Double_(a, b);
			}

			float Convert_Celsius_Fahrenheit(float degree)
			{
				return AVX_Scalar_Convert_Celsius_Fahrenheit_(degree);
			}

			float Convert_Fahrenheit_Celsius(float degree)
			{
				return AVX_Scalar_Convert_Fahrenheit_Celsius_(degree);
			}

			bool Convert_Number(const Uval* source, const Uval* destination, CvtOp operation)
			{
				return AVX_Scalar_Convert_Number_(source, destination, operation);
			}
		}
	}
}
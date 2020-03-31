#pragma once
#include <cstdint>
#include "types_avx.h"
#include "types_core.h"

using namespace Assembly::Core::Types;
using namespace Assembly::AVX::Types;

// AVX
extern "C" RoundingMode AVX_Get_Rounding_Mode_();
extern "C" void AVX_Set_Rounding_Mode_(const RoundingMode roundingMode);

// AVX / Packed
extern "C" void AVX_Packed_Array_Float_Sqtr_(float* input, const float* output, int arrayLength);
extern "C" void AVX_Packed_Compare_Doubles_Equal_(const XmmVal & a, const XmmVal & b, XmmVal results[]);
extern "C" bool AVX_Packed_Convert_Numbers_(const XmmVal & source, const XmmVal & destination, CvtOp operation);
extern "C" bool AVX_Packed_Find_Array_Float_Max_(const float* input, int arrayLength, float* result);
extern "C" bool AVX_Packed_Find_Array_Float_Min_(const float* input, int arrayLength, float* result);
extern "C" void AVX_Packed_Matrix_Float_Transpose_(float* input, const float* result);
extern "C" void AVX_Packed_Sum_Floats_(const XmmVal & a, const XmmVal & b, XmmVal results[]);

// AVX / Scalar
extern "C" double AVX_Scalar_Calc_Euclidian_Distance_(double x1, double y1, double z1, double x2, double y2, double z2);
extern "C" bool AVX_Scalar_Calc_Mean_Stdev_(const double* values, int arrayLength, double* mean, double* stdev);
extern "C" void AVX_Scalar_Calc_Sphere_Area_Volume_(double radius, double* area, double* volume);
extern "C" int AVX_Scalar_Compare_Double_VCMPSD_(double a, double b);
extern "C" int AVX_Scalar_Compare_Double_VCOMISD_(double a, double b);
extern "C" float AVX_Scalar_Convert_Celsius_Fahrenheit_(float degree);
extern "C" float AVX_Scalar_Convert_Fahrenheit_Celsius_(float degree);
extern "C" bool AVX_Scalar_Convert_Number_(const Uval * source, const Uval * destination, CvtOp operation);

// Core / Array
extern "C" int Core_Array_Compare_(const int* a, const int* b, int arraysLength, int** matchedValue);
extern "C" int Core_Array_Get_From_Const_ArrayLength_;
extern "C" int Core_Array_Get_From_Const_(int position, int* value);
extern "C" void Core_Array_Reverse_(const int* source, const int* destination, int arrayLength);
extern "C" int Core_Array_Sum_(const int* arrayPointer, int arrayLength);
extern "C" int Core_Array_Sum_Columns_(const int* sourceMatrix, const int* destinationArray, int numRows, int numColumns);

// Core / Math
extern "C" int Core_Math_Div_(int a, int b, int* quotient, int* remainder);
extern "C" int Core_Math_Max_(int a, int b, int c);
extern "C" int Core_Math_Max_v2_(int a, int b, int c);
extern "C" int Core_Math_Min_(int a, int b, int c);
extern "C" int Core_Math_Min_v2_(int a, int b, int c);
extern "C" int Core_Math_Sum_(int a, int b);

// Core / Stack
extern "C" int64_t Core_Stack_Sum_Arguments_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);
extern "C" double Core_Stack_Sum_Arguments_Xmm_(double a, double b, double c, double d, double e, double f, double g, double h);
extern "C" double Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_(double a, double b, double c, double d, double e, double f, double g, double h);

// Core / String
extern "C" size_t Core_String_Concat_(const char* const* source, size_t sourceElements, const char* destination, size_t destinationLength);
extern "C" int Core_String_Count_Char_Occurrence_(const char* text, char value);

// Core / Struct
extern "C" int Core_Struct_Get_CPU_Info_(const ProcessorInfo * processorInfo);
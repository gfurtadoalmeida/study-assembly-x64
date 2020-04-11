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
extern "C" bool AVX_Packed_Array_Max_Byte_(const uint8_t * input, uint32_t arrayLength, uint8_t * result);
extern "C" bool AVX_Packed_Array_Max_Float_(const float* input, uint32_t arrayLength, float* result);
extern "C" bool AVX_Packed_Array_Mean_Byte_(const uint8_t * input, uint32_t arrayLength, uint64_t * sum, double* mean);
extern "C" bool AVX_Packed_Array_Min_Byte_(const uint8_t * input, uint32_t arrayLength, uint8_t * result);
extern "C" bool AVX_Packed_Array_Min_Float_(const float* input, uint32_t arrayLength, float* result);
extern "C" void AVX_Packed_Array_Sqtr_Float_(float* input, uint32_t arrayLength, const float* result);
extern "C" void AVX_Packed_Compare_Equal_Double_(const XmmVal & a, const XmmVal & b, XmmVal results[]);
extern "C" bool AVX_Packed_Convert_Byte_To_Float_0_1_Range_(const uint8_t * input, uint32_t arrayLength, float* output);
extern "C" bool AVX_Packed_Convert_Float_To_Byte_0_255_Range(const float* input, uint32_t arrayLength, uint8_t * output);
extern "C" bool AVX_Packed_Convert_Number_(const XmmVal & source, const XmmVal & destination, CvtOp operation);
extern "C" bool AVX_Packed_Histogram_Gray_Image_(const uint8_t * pixels, uint32_t numPixels, uint32_t * histogram);
extern "C" void AVX_Packed_Matrix_Multiplication_Float_(const float* a, const float* b, float* result);
extern "C" void AVX_Packed_Matrix_Transpose_Float_(float* input, const float* result);
extern "C" void AVX_Packed_Multiply_Int_A_(const XmmVal & a, const XmmVal & b, XmmVal results[2]);
extern "C" void AVX_Packed_Multiply_Int_B_(const XmmVal & a, const XmmVal & b, XmmVal & results);
extern "C" void AVX_Packed_Multiply_Short_(const XmmVal & a, const XmmVal & b, XmmVal results[2]);
extern "C" bool AVX_Packed_Shift_Integer_(const XmmVal & input, XmmVal & results, ShiftOp shiftOp, uint32_t shiftCount);
extern "C" void AVX_Packed_Sum_Float_(const XmmVal & a, const XmmVal & b, XmmVal results[]);
extern "C" void AVX_Packed_Sum_Short_(const XmmVal & a, const XmmVal & b, XmmVal results[2]);

// AVX / Packed / 256 bits registers
extern "C" void AVX_Packed_Y_Abs_Double_(const YmmVal & input, YmmVal results[]);
extern "C" bool AVX_Packed_Y_Array_Cols_Mean_Double_(const double* input, uint32_t numRows, uint32_t numCols, double* colMeans);
extern "C" void AVX_Packed_Y_Blend_Float_(YmmVal * src1, YmmVal * src2, YmmVal * des, BlendSource blend[]);
extern "C" bool AVX_Packed_Y_Calc_Correlation_Coefficient_(const double* x, const double* y, size_t arrayLength, double sums[5], double epsilon, double* rho);
extern "C" void AVX_Packed_Y_Calc_Sphere_Area_Volume_(const float* radius, uint32_t arrayLength, float* areaa, float* volumea, float qnanValue);
extern "C" void AVX_Packed_Y_Matrix_Multiplication_Double_(const double* a, const double* b, double* result);
extern "C" void AVX_Packed_Y_Matrix_Transpose_Double_(double* input, const double* result);
extern "C" void AVX_Packed_Y_Permute_Float_(YmmVal * src, YmmVal * des, YmmVal * indexes);
extern "C" void AVX_Packed_Y_Sum_Float_(const YmmVal & a, const YmmVal & b, YmmVal results[]);

// AVX / Scalar
extern "C" double AVX_Scalar_Calc_Euclidian_Distance_(double x1, double y1, double z1, double x2, double y2, double z2);
extern "C" bool AVX_Scalar_Calc_Mean_Stdev_(const double* values, uint32_t arrayLength, double* mean, double* stdev);
extern "C" void AVX_Scalar_Calc_Sphere_Area_Volume_(double radius, double* area, double* volume);
extern "C" int32_t AVX_Scalar_Compare_VCMPSD_Double_(double a, double b);
extern "C" int32_t AVX_Scalar_Compare_VCOMISD_Double_(double a, double b);
extern "C" float AVX_Scalar_Convert_Celsius_Fahrenheit_(float degree);
extern "C" float AVX_Scalar_Convert_Fahrenheit_Celsius_(float degree);
extern "C" bool AVX_Scalar_Convert_Number_(const Uval * source, const Uval * destination, CvtOp operation);

// AVX2 / Packed
extern "C" bool AVX2_Packed_Clip_Pixel_Gray_Image_(PixelClipData * pcd);
extern "C" void AVX2_Packed_Convert_Float_HalfPrecision_(float values[8], uint16_t result[8], RoundingMode roudingMode);
extern "C" void AVX2_Packed_Convert_HalfPrecision_Float_(uint16_t values[8], float result[8]);
extern "C" void AVX2_Packed_Convert_Short_Int_(YmmVal * values, YmmVal result[2]);
extern "C" void AVX2_Packed_Convert_Short_Long_(YmmVal * values, YmmVal result[4]);
extern "C" void AVX2_Packed_Convert_UByte_UInt_(YmmVal * values, YmmVal result[4]);
extern "C" void AVX2_Packed_Convert_UByte_UShort_(YmmVal * values, YmmVal result[2]);
extern "C" void AVX2_Packed_Gather_Double_I32_(const double* src, double* des, const int32_t * indexes, const int64_t * merge);
extern "C" void AVX2_Packed_Gather_Double_I64_(const double* src, double* des, const int64_t * indexes, const int64_t * merge);
extern "C" void AVX2_Packed_Gather_Float_I32_(const float* src, float* des, const int32_t * indexes, const int32_t * merge);
extern "C" void AVX2_Packed_Gather_Float_I64_(const float* src, float* des, const int64_t * indexes, const int32_t * merge);
extern "C" void AVX2_Packed_Pack_I32_I16_(const YmmVal & a, const YmmVal & b, YmmVal * result);
extern "C" void AVX2_Packed_Permute_Float_(YmmVal * src, YmmVal * des, YmmVal * indexes);
extern "C" void AVX2_Packed_Sum_Int_(const YmmVal & a, const YmmVal & b, YmmVal & result);
extern "C" void AVX2_Packed_Sum_Short_(const YmmVal & a, const YmmVal & b, YmmVal & result);
extern "C" YmmValAB AVX2_Packed_Unpack_U32_U64_(const YmmVal & a, const YmmVal & b);

// AVX2  Scalar
extern "C" uint32_t AVX2_Scalar_And_Not_(uint32_t a, uint32_t b);
extern "C" void AVX2_Scalar_Count_Zero_Bits_(uint32_t value, uint32_t * leadingZeros, uint32_t * trailingZeros);
extern "C" uint32_t AVX2_Scalar_Extract_Bits_(uint32_t value, uint8_t start, uint8_t length);
extern "C" uint64_t AVX2_Scalar_Flagless_Multiply_UInt_(uint32_t a, uint32_t b, uint64_t flags[2]);
extern "C" void AVX2_Scalar_Flagless_Shift_UInt_(uint32_t value, uint32_t count, uint32_t results[3], uint64_t flags[4]);

// AVX-512 Scalar
extern "C" bool AVX512_Scalar_Calc_Sphere_Area_Volume_(double radius, double* area, double* volume, double errorValue);

// Core / Array
extern "C" int32_t Core_Array_Compare_(const int32_t * a, const int32_t * b, uint32_t arraysLength, int32_t * *matchedValue);
extern "C" uint32_t Core_Array_Get_From_Const_ArrayLength_;
extern "C" bool Core_Array_Get_From_Const_(uint32_t position, uint32_t * value);
extern "C" void Core_Array_Reverse_(const int32_t * source, const int32_t * destination, uint32_t arrayLength);
extern "C" int32_t Core_Array_Sum_(const int32_t * source, uint32_t arrayLength);
extern "C" bool Core_Array_Sum_Columns_(const int32_t * sourceMatrix, const int32_t * destinationArray, uint32_t numRows, uint32_t numColumns);

// Core / Math
extern "C" bool Core_Math_Div_(int32_t a, int32_t b, int32_t * quotient, int32_t * remainder);
extern "C" int32_t Core_Math_Max_(int32_t a, int32_t b, int32_t c);
extern "C" int32_t Core_Math_Max_v2_(int32_t a, int32_t b, int32_t c);
extern "C" int32_t Core_Math_Min_(int32_t a, int32_t b, int32_t c);
extern "C" int32_t Core_Math_Min_v2_(int32_t a, int32_t b, int32_t c);
extern "C" int32_t Core_Math_Sum_(int32_t a, int32_t b);

// Core / Stack
extern "C" int64_t Core_Stack_Sum_Arguments_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);
extern "C" double Core_Stack_Sum_Arguments_Xmm_(double a, double b, double c, double d, double e, double f, double g, double h);
extern "C" double Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_(double a, double b, double c, double d, double e, double f, double g, double h);

// Core / String
extern "C" uint32_t Core_String_Concat_(const char* const* source, uint32_t sourceElementsCount, const char* destination, uint32_t destinationLength);
extern "C" uint32_t Core_String_Count_Char_Occurrence_(const char* text, char value);

// Core / Struct
extern "C" bool Core_Struct_Get_CPU_Info_(const ProcessorInfo * processorInfo);

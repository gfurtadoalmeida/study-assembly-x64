#pragma once
#include <iomanip>
#include <string>
#include <sstream>

namespace Assembly {
	namespace AVX {
		namespace Types {

			enum class RoundingMode : uint32_t { Nearest, Down, Up, Truncate };

			// Must have the same order as defined in the
			// jump table of the following files:
			// - avx/packed/convert_numbers.asm 
			// - avx/scalar/convert_number.asm 
			enum class CvtOp : uint32_t {
				I32_F32, // int32_t to float
				F32_I32, // float to int32_t
				I32_F64, // int32_t to double
				F64_I32, // double to int32_t
				I64_F32, // int64_t to float
				F32_I64, // float to int64_t
				I64_F64, // int64_t to double
				F64_I64, // double to int64_t
				F32_F64, // float to double
				F64_F32, // double to float
			};

			// Must have the same order as defined in the
			// jump table of the following files:
			// - avx/packed/shift_integers.asm 
			enum class ShiftOp : uint32_t {
				// Logical = fill with zeros
				// Arithmetic = keeps signal bit

				U16_LOG_LEFT,    // Logical left - word
				U16_LOG_RIGHT,   // Logical right - word
				U16_ARITH_RIGHT, // Arithmetic right - word
				U32_LOG_LEFT,    // Logical left - doubleword
				U32_LOG_RIGHT,   // Logical right - doubleword
				U32_ARITH_RIGHT, // Arithmetic right - doubleword
			};

			union Uval
			{
				int32_t Int32;
				int64_t Int64;
				float Float;
				double Double;
			};

			struct XmmVal {
			public:
				union
				{
					int8_t Byte[16];
					int16_t Int16[8];
					int32_t Int32[4];
					int64_t Int64[2];
					uint8_t UByte[16];
					uint16_t UInt16[8];
					uint32_t UInt32[4];
					uint64_t UInt64[2];
					float Float[4];
					double Double[2];
				};
			private:
				template <typename T> std::string ToStringInt(const T* x, int n, int w)
				{
					std::ostringstream oss;

					for (int i = 0; i < n; i++)
					{
						oss << std::setw(w) << (int64_t)x[i];

						if (i + 1 == n / 2)
							oss << "   |";
					}

					return oss.str();
				}

				template <typename T> std::string ToStringUint(const T* x, int n, int w)
				{
					std::ostringstream oss;

					for (int i = 0; i < n; i++)
					{
						oss << std::setw(w) << (uint64_t)x[i];

						if (i + 1 == n / 2)
							oss << "   |";
					}

					return oss.str();
				}

				template <typename T> std::string ToStringHex(const T* x, int n, int w)
				{
					std::ostringstream oss;

					for (int i = 0; i < n; i++)
					{
						const int w_temp = 16;
						std::ostringstream oss_temp;

						oss_temp << std::uppercase << std::hex << std::setfill('0');
						oss_temp << std::setw(w_temp) << (uint64_t)x[i];
						std::string s1 = oss_temp.str();
						std::string s2 = s1.substr(w_temp - sizeof(T) * 2);

						oss << std::setw(w) << s2;

						if (i + 1 == n / 2)
							oss << "   |";
					}

					return oss.str();
				}

				template <typename T> std::string ToStringFP(const T* x, int n, int w, int p)
				{
					std::ostringstream oss;

					oss << std::fixed << std::setprecision(p);

					for (int i = 0; i < n; i++)
					{
						oss << std::setw(w) << x[i];

						if (i + 1 == n / 2)
							oss << "   |";
					}

					return oss.str();
				}

			public:

				//
				// Signed integer
				//

				std::string ToStringI8(void)
				{
					return ToStringInt(Byte, sizeof(Byte) / sizeof(int8_t), 4);
				}

				std::string ToStringI16(void)
				{
					return ToStringInt(Int16, sizeof(Int16) / sizeof(int16_t), 8);
				}

				std::string ToStringI32(void)
				{
					return ToStringInt(Int32, sizeof(Int32) / sizeof(int32_t), 16);
				}

				std::string ToStringI64(void)
				{
					return ToStringInt(Int64, sizeof(Int64) / sizeof(int64_t), 32);
				}

				//
				// Unsigned integer
				//

				std::string ToStringU8(void)
				{
					return ToStringUint(UByte, sizeof(UByte) / sizeof(uint8_t), 4);
				}

				std::string ToStringU16(void)
				{
					return ToStringUint(UInt16, sizeof(UInt16) / sizeof(uint16_t), 8);
				}

				std::string ToStringU32(void)
				{
					return ToStringUint(UInt32, sizeof(UInt32) / sizeof(uint32_t), 16);
				}

				std::string ToStringU64(void)
				{
					return ToStringUint(UInt64, sizeof(UInt64) / sizeof(uint64_t), 32);
				}

				//
				// Hexadecimal
				//

				std::string ToStringX8(void)
				{
					return ToStringHex(UByte, sizeof(UByte) / sizeof(uint8_t), 4);
				}

				std::string ToStringX16(void)
				{
					return ToStringHex(UInt16, sizeof(UInt16) / sizeof(uint16_t), 8);
				}

				std::string ToStringX32(void)
				{
					return ToStringHex(UInt32, sizeof(UInt32) / sizeof(uint32_t), 16);
				}

				std::string ToStringX64(void)
				{
					return ToStringHex(UInt64, sizeof(UInt64) / sizeof(uint64_t), 32);
				}

				//
				// Floating point
				//

				std::string ToStringF32(void)
				{
					return ToStringFP(Float, sizeof(Float) / sizeof(float), 16, 6);
				}

				std::string ToStringF64(void)
				{
					return ToStringFP(Double, sizeof(Double) / sizeof(double), 32, 12);
				}
			};
		}
	}
}
#pragma once

namespace Assembly {
	namespace AVX {
		namespace Types {

			enum class RoundingMode : uint32_t 
			{ 
				Nearest = 0b000, 
				Down = 0b001, 
				Up = 0b010, 
				Truncate = 0b011,
				SpecifiedInMxcsr = 0b100
			};

			// Must have the same order as defined in the
			// jump table of the following files:
			// - avx/packed/avx_p_convert_number.asm 
			// - avx/scalar/avx_p_convert_number.asm 
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
			// - avx/packed/avx_p_shift_integer.asm 
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

			enum class BlendSource : uint32_t
			{
				Source1 = 0x00000000,
				Source2 = 0x80000000
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
			};

			struct YmmVal {
			public:
				union
				{
					int8_t Byte[32];
					int16_t Int16[16];
					int32_t Int32[8];
					int64_t Int64[4];
					uint8_t UByte[32];
					uint16_t UInt16[16];
					uint32_t UInt32[8];
					uint64_t UInt64[4];
					float Float[8];
					double Double[4];
				};
			};

			struct alignas(32) YmmValAB
			{
				YmmVal A;
				YmmVal B;
			};

			struct ZmmVal {
			public:
				union
				{
					int8_t Byte[64];
					int16_t Int16[32];
					int32_t Int32[16];
					int64_t Int64[8];
					uint8_t UByte[64];
					uint16_t UInt16[32];
					uint32_t UInt32[16];
					uint64_t UInt64[8];
					float Float[16];
					double Double[8];
				};
			};

			// Must have the same definition as
			// defined in the following files:
			// - avx2/packed/avx2_p_clip_pixel_gray_image.asm
			struct PixelClipData {
				uint8_t* Source;
				uint8_t* Destination;
				uint64_t NumPixels;
				uint64_t NumClippedPixels;
				uint8_t ThresholdLow;
				uint8_t ThresholdHigh;
			};

			typedef struct {
				double X;
				double Y;
				double Z;
			} Vector;

			struct Vector4x1_F32
			{
				float W;
				float X;
				float Y;
				float Z;
			};
		}
	}
}
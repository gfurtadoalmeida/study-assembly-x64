# Annotations

The annotations below are for x64 systems/CPUs.

## CPU

Just the essentials as this is focused on Assembly and not CPU internals.

### Organization

```text
Based on Intel Core i7 8570H (6 cores, but only 4 are shown).
┌───────────────────────────────────────────────────────────────┐
│                       MEMORY CONTROLLER                       │
├───────────────┬───────────────┬───────────────┬───────────────┤
│      CORE     │      CORE     │      CORE     │      CORE     │
│ ┌───────────┐ │ ┌───────────┐ │ ┌───────────┐ │ ┌───────────┐ │
│ │ REGISTERS │ │ │ REGISTERS │ │ │ REGISTERS │ │ │ REGISTERS │ │
│ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │
│ │ L1 CACHE  │ │ │ L1 CACHE  │ │ │ L1 CACHE  │ │ │ L1 CACHE  │ │
│ │ D - 32 Kb │ │ │ D - 32 Kb │ │ │ D - 32 Kb │ │ │ D - 32 Kb │ │
│ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │
│ │ L1 CACHE  │ │ │ L1 CACHE  │ │ │ L1 CACHE  │ │ │ L1 CACHE  │ │
│ │ I - 32 Kb │ │ │ I - 32 Kb │ │ │ I - 32 Kb │ │ │ I - 32 Kb │ │
│ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │ ├───────────┤ │
│ │ L2 CACHE  │ │ │ L2 CACHE  │ │ │ L2 CACHE  │ │ │ L2 CACHE  │ │
│ │   256 Kb  │ │ │   256 Kb  │ │ │   256 Kb  │ │ │   256 Kb  │ │
│ └───────────┘ │ └───────────┘ │ └───────────┘ │ └───────────┘ │
├───────────────┴───────────────┴───────────────┴───────────────┤
│                         L3 CACHE - 9 Mb                       │
└───────────────────────────────────────────────────────────────┘
```
  
### Cache [:link:](https://en.wikipedia.org/wiki/CPU_cache)

Each _physical core_ has two cache layers (L1, L2), and all cores share one cache layer (L3).
L1 cache is divided in:

* L1 D: data cache
* L1 I: instruction cache

Data is transferred between memory and cache in blocks of fixed size (_usually 64 bytes_), called cache lines or cache blocks.

For every memory access(read/write) the CPU will:

1. Verify if the data is not already in L1, L2 or L3.
2. Load the data from memory (with cache line size) to L3 -> L2 -> L1.
3. If the data does not fit into a layer, some older data will be evicted and transferred to a lower layer.

Writes to main memory can happen in two ways:

* Write-through: a write to the cache causes a write to main memory.
* Write-back: only write to main memory when a cache line is evicted.

### Registers [:link:](https://en.wikipedia.org/wiki/Processor_register)

A quickly (faster than L1) accessible location, _available per CPU core_, usually consisting of a small amount of fast storage, although some registers have specific hardware functions, and may be read-only or write-only.  

Almost all CPUs, whether load/store architecture or not, load data from a larger memory into registers where it is used by other operations.  

#### General Purpose

Stores both data and addresses.

RAX: accumulator.  
RBX: base.  
RCX: counter.  
RDX: data.

```text
63                             31                               0
┌───────────────────────────────────────────────────────────────┐
│                            RAX 64 b                           │
├───────────────────────────────┬───────────────────────────────┤
│                               │            EAX 32 b           │
├───────────────────────────────┴───────────────┬───────────────┤
│                                               │    AX 16 b    │
├───────────────────────────────────────────────┼───────┬───────┤
│                                               │ AH 8b │ AL 8b │
└───────────────────────────────────────────────┴───────┴───────┘
```

R8-R15.

```text
63                             31                               0
┌───────────────────────────────────────────────────────────────┐
│                            R8 64 b                            │
├───────────────────────────────┬───────────────────────────────┤
│                               │            R8D 32 b           │
├───────────────────────────────┴───────────────┬───────────────┤
│                                               │    R8W 16 b   │
├───────────────────────────────────────────────┴──────┬────────┤
│                                                      │ R8B 8b │
└──────────────────────────────────────────────────────┴────────┘
* It's not possible to access the upper 8 bits of R8W.
```

#### Index

Used for indexed addressing (usually string functions) and sometimes used in addition and subtraction.  

RSI: source index.
RDI: destination index.

```text
63                             31                               0
┌───────────────────────────────────────────────────────────────┐
│                            RSI 64 b                           │
├───────────────────────────────┬───────────────────────────────┤
│                               │            ESI 32 b           │
├───────────────────────────────┴───────────────┬───────────────┤
│                                               │    SI 16 b    │
└───────────────────────────────────────────────┴───────────────┘
```

#### Pointer

RBP (base pointer): helps in referencing the parameter variables passed to a subroutine.  
RIP (instruction pointer): offset address of the next instruction to be executed.  
RSP (stack pointer): offset value within the program stack.

```text
63                             31                               0
┌───────────────────────────────────────────────────────────────┐
│                            RBP 64 b                           │
├───────────────────────────────┬───────────────────────────────┤
│                               │            EBP 32 b           │
├───────────────────────────────┴───────────────┬───────────────┤
│                                               │    BP 16 b    │
└───────────────────────────────────────────────┴───────────────┘
```

#### Segment [:link:](https://en.wikipedia.org/wiki/X86_memory_segmentation)

Stores the starting location of segments present in memory, related to the whole process, not method being executed.  
All memory locations within a segment are relative to the starting address of the segment.  

CS (code/text segment): starting address of the [code segment](https://en.wikipedia.org/wiki/Code_segment).
DS (data segment): starting address of the [data segment](https://en.wikipedia.org/wiki/Data_segment).
ES (extra segment): free memory segment.
FS: on Windows is used to access the thread information block and exception handling chain.
GS: on Windows is used to access the thread local storage.
SS (stack segment): starting address of the stack.

**On x64 only FS and GS are used.**

#### Status

##### RFLAGS [:link:](https://en.wikipedia.org/wiki/FLAGS_register)

Collection of status flag bits that are generally modified as effects of arithmetic and bit manipulation operations of **x86/x64** instructions.  

```text
63       22            15                             0
┌──────────┬─┬─┬─┬─┬─┬─┬─┬─┬───┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
│          │I│V│V│A│V│R│ │N│IO │O│D│I│T│S│Z│ │A│ │P│ │C│
│ RESERVED │D│I│I│C│M│F│ │T│PL │F│F│F│F│F│F│ │F│ │F│ │F│
│          │ │P│F│ │ │ │ │ │   │ │ │ │ │ │ │ │ │ │ │ │ │
└──────────┴─┴─┴─┴─┴─┴─┴─┴─┴───┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
            │ │ │ │ │ │   │  │  │ │ │ │ │ │   │   │   └ Carry
            │ │ │ │ │ │   │  │  │ │ │ │ │ │   │   └──── Parity
            │ │ │ │ │ │   │  │  │ │ │ │ │ │   └──────── Adjust
            │ │ │ │ │ │   │  │  │ │ │ │ │ └──────────── Zero
            │ │ │ │ │ │   │  │  │ │ │ │ └────────────── Sign
            │ │ │ │ │ │   │  │  │ │ │ └──────────────── Trap
            │ │ │ │ │ │   │  │  │ │ └────────────────── Interrupt enabled
            │ │ │ │ │ │   │  │  │ └──────────────────── Direction
            │ │ │ │ │ │   │  │  └────────────────────── Overflow
            │ │ │ │ │ │   │  └───────────────────────── I/O privilege level
            │ │ │ │ │ │   └──────────────────────────── Nested task
            │ │ │ │ │ └──────────────────────────────── Resume
            │ │ │ │ └────────────────────────────────── Virt. 8086 mode
            │ │ │ └──────────────────────────────────── Alignment check
            │ │ └────────────────────────────────────── Virt. interrupt
            │ └──────────────────────────────────────── Virt. interrupt pending
            └────────────────────────────────────────── CPUID available
```

Commonly used flags:

|  Bit  | Name                     | =1              | =0                 |
| :---: | :----------------------- | --------------- | ------------------ |
|   0   | CF = Carry               | CY = Carry      | NC = No Carry      |
|   2   | PF = Parity              | PE = Even       | PO = Odd           |
|   4   | AF = Adjust              | AC = Aux. Carry | NA = No Aux. Carry |
|   6   | ZF = Zero                | ZR = Zero       | NZ = Not Zero      |
|   7   | SF = Sign                | NG = Negative   | PL = Positive      |
|  10   | DF = Direction (get/set) | DN = Down       | UP = Up            |
|  11   | OF = Overflow            | OV = Overflow   | NV = Not Overflow  |

##### MXCSR [:link:](https://softpixel.com/~cwright/programming/simd/sse.php)

Collection of status flag bits that are generally modified as effects of arithmetic and bit manipulation operations of **vector (SSE, AVX)** instructions.  

```text
31                     15                             0
┌──────────────────────┬─┬──┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
│                      │F│RC│P│U│O│Z│D│I│D│P│U│O│Z│D│I│
│ RESERVED             │Z│  │M│M│M│M│M│M│A│E│E│E│E│E│E│
│                      │ │  │ │ │ │ │ │ │Z│ │ │ │ │ │ │
└──────────────────────┴─┴──┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
                        │  │ │ │ │ │ │ │ │ │ │ │ │ │ └ Invalid Operation
                        │  │ │ │ │ │ │ │ │ │ │ │ │ └── Denormal
                        │  │ │ │ │ │ │ │ │ │ │ │ └──── Divide-by-zero
                        │  │ │ │ │ │ │ │ │ │ │ └────── Overflow
                        │  │ │ │ │ │ │ │ │ │ └──────── Underflow
                        │  │ │ │ │ │ │ │ │ └────────── Precision
                        │  │ │ │ │ │ │ │ └──────────── Denormals are zero
                        │  │ │ │ │ │ │ └────────────── Invalid operation mask
                        │  │ │ │ │ │ └──────────────── Denormal operation mask
                        │  │ │ │ │ └────────────────── Divide-by-zero mask
                        │  │ │ │ └──────────────────── Overflow mask
                        │  │ │ └────────────────────── Underlfow mask
                        │  │ └──────────────────────── Precision mask
                        │  └────────────────────────── Rounding control  
                        └───────────────────────────── Flush to zero
```

* PM, UM, MM, ZM, DM, and IM: tells the processor to ignore the exceptions that happen.
* PE, UE, ME, ZE, DE, and IE: set when any unmasked exception happen.
* Error flags **ARE NOT** automatically cleared by the processor after an error is detected; they must be manually cleared.  

Rounding control:

| Name                   | Bit 13 | Bit 14 |
| ---------------------- | :----: | :----: |
| RN = Nearest (default) |   0    |   0    |
| R+ = Positive          |   0    |   1    |
| R- = Negative          |   1    |   0    |
| RZ = To Zero           |   1    |   1    |

#### Vector [:link:](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions)

Added with AVX, AVX2 and AVX-512, holds data for vector processing done by SIMD instructions.  

SSE: XMM0-15, 128 bits.
AVX: YMM0-15, 256 bits.
AVX-512: ZMM0-31, 512 bits.

```text
511                            255                              0
┌───────────────────────────────────────────────────────────────┐
│                            ZMM 512 b                          │
├───────────────────────────────┬───────────────────────────────┤
│                               │            YMM 256 b          │
├───────────────────────────────┴───────────────┬───────────────┤
│                                               │   XMM 128 b   │
└───────────────────────────────────────────────┴───────────────┘
```

#### Vector Operation Mask [:link:](https://en.wikipedia.org/wiki/AVX-512#Opmask_registers)

Added with AVX-512, primarily used as predicate masks to perform conditional executions and merging operations. They can also be employed as destination operands for instructions that generate vector mask results.

The number of bits used depends on the vector type. For a double (64 bits), only 8 bits will suffice (512 b / 64 b = 8).

K0-K7

```text
63                                                              0
┌───────────────────────────────────────────────────────────────┐
│                         AVX-512BW 63 b                        │
├───────────────────────────────────────────────┬───────────────┤
│                                               │  AVX-512 16 b │
└───────────────────────────────────────────────┴───────────────┘
```

## Memory

### Alignment [:link:](https://en.wikipedia.org/wiki/Data_structure_alignment)

A properly-aligned data type is one whose address is evenly divisible by its size in bytes. As example, storing a 64 bits number (8 bytes) at address 108678 would make it proper-aligned as 108768 % 8 == 0.

Proper alignment is important for performance as some instructions, when operating with unaligned addresses takes more cycles to complete.

Common alignments (in bytes):

* 16: XMM operands
* 32 YMM operands
* 64 ZMM operands

### Endianness [:link:](https://en.wikipedia.org/wiki/Endianness)

How the bytes of a multi-byte value is represented in memory.

* Big-endian: the most significant byte first and the least significant byte last.
* Little-endian: the least significant byte first and the most significant byte last

Take the number 24.712 (16 bits, 2 bytes) and it's binary representation 01100000_10001000:

* Big-endian: #A0 = 01100000, #A1 = 10001000
* Little-endian: #A0 = 10001000, #A1 = 01100000

x86-x64 architectures uses **little-endian**.

## Visual C++ x64 Software Conventions [:link:](https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions?view=vs-2019)

### Registers

| Function                     | Type        | Name(s)                | Preserve |
| ---------------------------- | ----------- | ---------------------- | :------: |
| Arguments (integer)          | Volatile    | ECX, EDX, R8, R9       |    -     |
| Arguments (real and vectors) | Volatile    | Z/Y/XMM0-3             |    -     |
| Arguments (real and vectors) | Volatile    | Z/Y/XMM4-5             |    Y     |
| Frame pointer                | Nonvolatile | RBP                    |    Y     |
| Return value (integer)       | Volatile    | EAX                    |    -     |
| Return value (real)          | Volatile    | Z/Y/XMM0               |    -     |
| Scratchpad (integer)         | Nonvolatile | R12-R15, RBX, RDI, RSI |    Y     |
| Scratchpad (real and vector) | Nonvolatile | Z/Y/XMM6-15            |    Y     |
| Scratchpad (real and vector) | Volatile    | Z/Y/XMM16-31           |    -     |
| Stack pointer                | Nonvolatile | RSP                    |    Y     |
| Syscall/sysret instructions  | Volatile    | R10, R11               |    Y     |

Registers marked as nonvolatile or preserve **MUST HAVE** their values saved (pushed to stack) before being used and **MUST HAVE** their values restored before the method returns.  

### Stack Usage

```text
argument z     <─┬─┬─ rsp + offset (higher address)
   .             │░│
   .             │░│
   .             │░│
argument a       │░│
r9  home         │░├─ OS stack allocated memory
r8  home         │░│
rdx home         │░│
rcx home         │░│
return address   │░│
saved old rbp  <─┼─┼─ rsp (grows to lower address)
local var a      │▓│
local var b      │▓│
   .             │▓├─ user stack allocated memory
   .             │▓│
   .             │▓│
local var z    <─┴─┴─ rsp - offset (lower address)
```

### Prolog and Epilog

Instructions that **MUST BE** at the beginning (_prolog_) and end (_epilog_) of any method that allocates stack space, calls other functions, saves nonvolatile registers, or uses exception handling.

Prolog:

1. Push RBP to stack.
2. Push used nonvolatile/preserve registers to stack.
3. Decremented RSP the bytes necessary to allocate memory on the stack.
4. Copy RSP value to RBP.

Epilog:

1. Increment RSP the same amount it was decremented; release the stack memory.
2. Pop nonvolatile/preserve registers from stack.
3. Pop RBP from the stack.
4. Call _vzeroupper_ in case any 256 bits register (YMM) was used.

### Returning a Struct by Value

When returning a struct by value, RCX will contain a pointer to a temporary buffer allocated to the struct and all parameters will be shifted one register to the right.  

The first three arguments will be passed using registers RDX/XMM1, R8/XMM2, and R9/XMM3. Any remaining arguments are passed on the stack.  

Beware that the buffer allocated **IS NOT** necessarily the final memory location.  

This type of return is slow because Visual C++ will allocate a variable to hold the intermediate value (temporary buffer) and then will move it to a final memory location.  

Responsibilities:

* Caller: allocate the temporary buffer and store the pointer on RCX prior calling a function that returns struct by value.
* Called: copy RCX to RAX prior returning.

## Assembly

* Colon notation: signifies that a result is contained in two registers, where the first register holds the high-order bits (e.g EAX:ECX = EAX high order bits and ECX low-order bits).
* Effective Address: _BaseRegister + IndexRegister * ScaleFactor + Displacement_.
* Flagless instruction: executes its operation without modifying RFLAGS, which can be faster than an equivalent flag-based instruction.
* Operands:
  * Immediate: a constant
  * Register: a register
  * Memory: a memory location
* Non-Temporal data: value that is accessed once and not immediately reused. Can degrade performance when cache has excessive amount of this type of data.
* Saturated arithmetic: results are clipped at max/min value of the data type to prevent overflow/underflow.

### 64 Bit Mode

When an x86 processor is running in 64-bit mode, instructions that employ 32-bit operands produce 32-bit results. If the destination operand is a 32-bit register, the high-order 32 bits (63-32) are zeroed.  

The product of two 32-bit integers is always a 64-bit result.

### Instructions

* String: require that addresses of source and destination operands to be placed in registers RSI (source) and RDI (destination).
* MMX and x87 FPU: recommended not to use as they're legacy instructions.  

### Bridging with Visual C++

To use a struct in both C++ and assembly code, it must be declared twice (.cpp, .asm) and both declarations must be semantically equivalent.  

Visual C++ assumes that the RFLAGS.DF is always cleared and hence the flag **MUST BE** cleared before returning to the caller in case the flag was altered.

### SSE, AVX, AVX-2 and AVX-512

When mixing SSE and AVX operations **IS IMPERATIVE** to call _vzeroupper_ to clear all bits above a XMM register, so as to not incur on performance penalty.  

When using aligned instructions, all memory operand **MUST BE** aligned on:

* XMM: 16 bytes
* YMM: 32 bytes
* ZMM: 64 bytes

Control masks determines whether or not a instruction will operate or not on a  particular element on the destination operand.  

Fused-multiply-add/subtract are instructions that perform a floating-point multiplication followed by a floating-point addition/subtraction using a single rounding operation using the rounding mode specified by MXCSR.RC.  

### Performance Tips

#### Basic

Avoid using:

* Instructions that require an operand-size prefix to load a 16-bit immediate value (_mov dx, 42_).
* Instructions that perform partial updates of the status flags in RFLAGS.
* Memory-immediate forms of _cmp_ and _test_ (_cmp dword ptr [rbp + 40], 100_ or _test byte ptr [r12], 0fh_). Load the value on a register first and then compare.
* _lea_ that contains three effective address components (base register, index register, displacement) in performance-critical processing loops.

Use:

* 32-bit instead of 64-bit instruction forms and general-purpose registers.
* 32-bit instruction forms to load 64-bit registers with positive constant values (_mov eax, 16_).
* _imul_ in the two or three operand form to multiply two signed integers when the full-width product is not needed.
* _test_ instead of _cmp_ to test for less than, equal to, or greater than zero.
* _xor_ or _sub_ to zero a register.

Load any memory values that are needed for multiple calculations into a register.

#### Floating-Pointing

Avoid:

* Arithmetic underflows and denormal values during arithmetic calculations.
* Using denormalized floating-point constants.
* Using Legacy x87 floating-point unit.

Do:

* Arrange floating-point instruction sequences to minimize register dependencies.
* Partially (or completely) unroll processing loops that contain floating-point calculations.
* Set MXCSR:
  * DAZ to 1 when rounding of a denormal (number that is so small that FPU can't renormalize it due to limited exponent ranges) to zero is acceptable.
  * FZ to 1 when floating-point underflows are common.
* Use single-precision floating-point values instead of double-precision values.

#### Branches

Do:

* Align branch targets in performance-critical loops to 16-byte boundaries.
* Minimize the number of branches.
* Move conditional code that is unlikely to execute (error-handling) to another program (or .code) section or memory page.
* Partially (or completely) unroll short processing loops

Use:

* _setcc_ or _cmovcc_ to eliminate unpredictable data-dependent branches.
* Forward conditional jumps when the fall-through code is more likely to execute.
* Backward conditional jumps when the fall-through code is less likely to execute.

#### Data Alignment

Align:

* 128, 256, and 512-bit wide packed integer and floating-point values to 16, 32 and 64 bytes.
* Multi-byte integer and floating-point values to their natural boundaries.
* And position small arrays and short text strings in a data structure to avoid cache line splits^1^.

Do:

* Pad data structures to ensure proper alignment of each structure member.
* Prefer aligned stores over aligned loads.

^1^ A cache line split occurs when the bytes of a multi-byte value are split across a 64-byte boundary. Positioning small multi-byte values on the same cache line helps minimize the number of memory cycles that the processor must perform.

#### SIMD Techniques

Avoid:

* Intermixing x86-AVX and x86-SSE instructions.
* Cache pollution by using non-temporal store instructions (_vmovntdqa_, _vmovntp_, etc.).

Do:

* Load multiple-use memory operands and packed constants into a register.
* Minimize register dependencies to exploit multiple Execution Units in the Execution Engine.
* Process SIMD arrays using small data blocks to maximize reuse of resident cache data.

Use:

* Extra SIMD registers to minimize data dependencies and register spills^1^.
* Data prefetch instructions (_prefetcht0_, _prefetchnta_, etc.) to notify the processor of expected-use data items.
* Masking and boolean operations to minimize or eliminate data-dependent conditional jump.
* The doubleword forms of the gather and scatter instructions instead of the quadword forms.
* _vpxor, vxorp_ to zero a register.
* _vzeroupper_ to avoid x86-AVX to x86-SSE transition penalties.

^1^  A register spill occurs when a function must temporarily save the contents of a register to memory in order to free the register for other calculations.
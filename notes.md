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

#### Status (RFLAGS) [:link:](https://en.wikipedia.org/wiki/FLAGS_register)

Collection of status flag bits that are generally modified as effects of arithmetic and bit manipulation operations.  

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
            │ └──────────────────────────────────────── irt. interrupt pending
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

#### Vector [:link:](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions)

Added with AVX, AVX2 and AVX-512, holds data for vector processing done by SIMD instructions.  

XMM0-15, YMM0-15, ZMM0-31

```text
511                            255                              0
┌───────────────────────────────────────────────────────────────┐
│                            ZMM 512 b                          │
├───────────────────────────────┬───────────────────────────────┤
│                               │            YMM 256 b          │
├───────────────────────────────┼───────────────┬───────────────┤
│                               │               │   XMM 128 b   │
└───────────────────────────────┴───────────────┴───────────────┘
```

#### Vector Opmask [:link:](https://en.wikipedia.org/wiki/AVX-512#Opmask_registers)

Added with AVX-512, primarily used as predicate masks to perform conditional executions and merging operations. They can also be employed as destination operands for instructions that generate vector mask results.

The number of bits used depends on the vector type. For a double (64 bits), only 8 bits will suffice (512 b / 64 b = 8).

K0-K7

```text
63                                                              0
┌───────────────────────────────────────────────────────────────┐
│                         AVX-512BW 63 b                        │
├───────────────────────────────────────────────┬───────────────┤
│                                               │      16 b     │
└───────────────────────────────────────────────┴───────────────┘
```

## Visual C++ x64 Software Conventions [:link:](https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions?view=vs-2019)

### Registers

| Function                     | Type        | Name(s)                | Preserve |
| ---------------------------- | ----------- | ---------------------- | :------: |
| Arguments (integer)          | Volatile    | ECX, EDX, R8, R9       |    -     |
| Arguments (real and vectors) | Volatile    | Y/XMM0-3               |    -     |
| Arguments (real and vectors) | Volatile    | Y/XMM4-5               |    Y     |
| Frame pointer                | Nonvolatile | RBP                    |    Y     |
| Return value (integer)       | Volatile    | EAX                    |    -     |
| Return value (real)          | Volatile    | Z/Y/XMM0               |    -     |
| Scratchpad (integer)         | Nonvolatile | R12-R15, RBX, RDI, RSI |    Y     |
| Scratchpad (real and vector) | Nonvolatile | Z/Y/XMM6-15            |    Y     |
| Scratchpad (real and vector) | Volatile    | Z/Y/XMM16-31           |    -     |
| Stack pointer                | Nonvolatile | RSP                    |    Y     |
| Syscall/sysret instructions  | Volatile    | R10, R11               |    Y     |

Registers marked as nonvolatile or preserve **MUST** have their values saved (pushed to stack) before being used and **MUST** have their values restored before the method returns.  

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

Instructions that **MUST** be at the beginning (_prolog_) and end (_epilog_) of any method that allocates stack space, calls other functions, saves nonvolatile registers, or uses exception handling.

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

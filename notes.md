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
  
### [Cache](https://en.wikipedia.org/wiki/CPU_cache)

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

### [Registers](https://en.wikipedia.org/wiki/Processor_register)

A quickly (faster than L1) accessible location, _available per CPU core_, usually consisting of a small amount of fast storage, although some registers have specific hardware functions, and may be read-only or write-only.  

Almost all CPUs, whether load/store architecture or not, load data from a larger memory into registers where it is used by other operations.  

#### General Purpose

Stores both data and addresses.

RAX, RBX, RCX, RDX, RBP, RSI, RDI, RSP.

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

R8-R15

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

#### [Program Counter (RIP)](https://en.wikipedia.org/wiki/Program_counter)

Holds the memory address of the next instruction to be executed.

#### [Status (RFLAGS)](https://en.wikipedia.org/wiki/FLAGS_register)

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

Most important flags:  

|  Bit  | Name                     | =1              | =0                 |
| :---: | :----------------------- | --------------- | ------------------ |
|   0   | CF = Carry               | CY = Carry      | NC = No Carry      |
|   2   | PF = Parity              | PE = Even       | PO = Odd           |
|   4   | AF = Adjust              | AC = Aux. Carry | NA = No Aux. Carry |
|   6   | ZF = Zero                | ZR = Zero       | NZ = Not Zero      |
|   7   | SF = Sign                | NG = Negative   | PL = Positive      |
|  10   | DF = Direction (get/set) | DN = Down       | UP = Up            |
|  11   | OF = Overflow            | OV = Overflow   | NV = Not Overflow  |

#### Vector

Holds data for vector processing done by SIMD instructions.  

[XMM0-15, YMM0-15, ZMM0-31](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions)

```text
511                            255                              0
┌───────────────────────────────────────────────────────────────┐
│                            ZMM 512 b                          │
├───────────────────────────────┬───────────────────────────────┤
│                               │            YMM 256 b          │
├───────────────────────────────┼───────────────┬───────────────┤
│                               |               │   XMM 128 b   │  
└───────────────────────────────┴───────────────┴───────────────┘
```

## [Assembly](https://en.wikipedia.org/wiki/Assembly_language)

Low-level programming language in which there is a very strong correspondence between the instructions in the language and the architecture's machine code instructions; your code will only work on certain CPU architectures.

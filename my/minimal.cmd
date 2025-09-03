/* Minimal C7000 linker command file */

MEMORY
{
    /* Define memory regions (addresses are example values) */
    L2RAM   (RWX) : origin = 0x00800000, length = 0x00100000   /* 1 MB */
    MSMC    (RWX) : origin = 0x70000000, length = 0x00800000   /* 8 MB */
    DDR     (RWX) : origin = 0x80000000, length = 0x40000000   /* 1 GB */
}

SECTIONS
{
    /* Code and constants go into L2RAM by default */
    .text       > L2RAM
    .const      > L2RAM
    .cinit      > L2RAM
    .pinit      > L2RAM

    /* Initialized and uninitialized data */
    .data       > L2RAM
    .bss        > L2RAM

    /* Stack and heap */
    .stack      > L2RAM
    .heap       > L2RAM
}


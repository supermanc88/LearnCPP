#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===============================
   hex char -> int
   =============================== */

static inline int hexchar2int(unsigned char c)
{
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;

        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
    }

    return -1;
}

/* ===============================
   hex -> bin
   =============================== */

int hex2bin(const char* src, size_t len, uint8_t* dst)
{
    if (len % 2)
        return -1;

    size_t i;
    for (i = 0; i < len; i += 2) {

        int hi = hexchar2int(src[i]);
        int lo = hexchar2int(src[i + 1]);

        if (hi < 0 || lo < 0)
            return -2;

        dst[i / 2] = (hi << 4) | lo;
    }

    return 0;
}


/* ===============================
   bin -> hex
   =============================== */

static const char hexdig[] = "0123456789ABCDEF";

void bin2hex(const uint8_t *bin, size_t len, char *out)
{
    size_t i;

    for (i = 0; i < len; i++) {
        out[i * 2]     = hexdig[(bin[i] >> 4) & 0xF];
        out[i * 2 + 1] = hexdig[bin[i] & 0xF];
    }

    // out[len * 2] = '\0';
}


/* ===============================
   test
   =============================== */

double now()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,&t);
    return t.tv_sec + t.tv_nsec*1e-9;
}

#define DATA_SIZE (64*1024*1024)   // 64MB
#define LOOPS 50

int main()
{
    /* ===========================
   benchmark
   gcc -O3 -o test_fast main.c

    ./test_fast
    data size = 64 MB
    bin2hex speed: 1.92 GB/s
    hex2bin speed: 0.11 GB/s
   =========================== */

    uint8_t *bin = malloc(DATA_SIZE);
    char *hex = malloc(DATA_SIZE*2);
    uint8_t *bin2 = malloc(DATA_SIZE);

    for(size_t i=0;i<DATA_SIZE;i++)
        bin[i] = rand();

    printf("data size = %d MB\n",(int)(DATA_SIZE/1024/1024));

    /* bin2hex */

    double t1 = now();

    for(int i=0;i<LOOPS;i++)
        bin2hex(bin,DATA_SIZE,hex);

    double t2 = now();

    double seconds = t2-t1;

    double throughput =
        ((double)DATA_SIZE*LOOPS)/(1024.0*1024.0*1024.0)/seconds;

    printf("bin2hex speed: %.2f GB/s\n",throughput);

    /* hex2bin */

    t1 = now();

    for(int i=0;i<LOOPS;i++)
        hex2bin(hex,DATA_SIZE*2,bin2);

    t2 = now();

    seconds = t2-t1;

    throughput =
        ((double)DATA_SIZE*LOOPS)/(1024.0*1024.0*1024.0)/seconds;

    printf("hex2bin speed: %.2f GB/s\n",throughput);

    free(bin);
    free(hex);
    free(bin2);

    return 0;
}
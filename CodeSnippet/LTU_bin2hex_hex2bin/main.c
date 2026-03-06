#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

static const char hex_table[512] = {
#define HEX_PAIR(x) \
"0123456789ABCDEF"[(x)>>4], "0123456789ABCDEF"[(x)&0xf]

#define ROW16(x) \
HEX_PAIR(x),HEX_PAIR(x+1),HEX_PAIR(x+2),HEX_PAIR(x+3), \
HEX_PAIR(x+4),HEX_PAIR(x+5),HEX_PAIR(x+6),HEX_PAIR(x+7), \
HEX_PAIR(x+8),HEX_PAIR(x+9),HEX_PAIR(x+10),HEX_PAIR(x+11), \
HEX_PAIR(x+12),HEX_PAIR(x+13),HEX_PAIR(x+14),HEX_PAIR(x+15)

    ROW16(0x00),ROW16(0x10),ROW16(0x20),ROW16(0x30),
    ROW16(0x40),ROW16(0x50),ROW16(0x60),ROW16(0x70),
    ROW16(0x80),ROW16(0x90),ROW16(0xA0),ROW16(0xB0),
    ROW16(0xC0),ROW16(0xD0),ROW16(0xE0),ROW16(0xF0)

    #undef ROW16
    #undef HEX_PAIR
    };

void bin2hex_fast(const uint8_t* src, size_t len, char* dst)
{
    const char* lut = hex_table;

    for (size_t i = 0; i < len; i++) {
        uint8_t v = src[i];
        dst[i*2]   = lut[v*2];
        dst[i*2+1] = lut[v*2+1];
    }
}

static const uint8_t hex_to_bin[256] = {
    ['0']=0,['1']=1,['2']=2,['3']=3,['4']=4,
    ['5']=5,['6']=6,['7']=7,['8']=8,['9']=9,

    ['a']=10,['b']=11,['c']=12,['d']=13,['e']=14,['f']=15,
    ['A']=10,['B']=11,['C']=12,['D']=13,['E']=14,['F']=15
};

int hex2bin_fast(const char* src, size_t len, uint8_t* dst)
{
    if (len & 1) return -1;

    for (size_t i=0;i<len;i+=2)
    {
        uint8_t hi = hex_to_bin[(uint8_t)src[i]];
        uint8_t lo = hex_to_bin[(uint8_t)src[i+1]];

        dst[i/2] = (hi<<4) | lo;
    }

    return 0;
}

#define DATA_SIZE (64*1024*1024)   // 64MB
#define LOOPS 50

/* ===========================
   timer
   =========================== */

double now()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,&t);
    return t.tv_sec + t.tv_nsec*1e-9;
}

int main()
{
    // uint8_t data[] = {0xde,0xAD,0xbe,0xEF};
    //
    // char hex[128] = {0};
    // uint8_t out[128] = {0};
    // size_t outlen;
    //
    // bin2hex_fast(data,4,hex);
    //
    // printf("bin2hex: %s\n",hex);
    //
    // memcpy(hex,"abcdefcd", 8);
    //
    // hex2bin_fast(hex,8,out);
    //
    // printf("hex2bin: ");
    //
    // for(size_t i=0;i<4;i++)
    //     printf("%02X",out[i]);
    //
    // printf("\n");

    /* ===========================
       benchmark
    gcc -O3 -o test_LTU main.c

    ./test_LTU
    data size = 64 MB
    sink: A
    bin2hex speed: 3.28 GB/s
    sink: FFFFFFA7
    hex2bin speed: 1.92 GB/s
       =========================== */

    volatile char sink;

    uint8_t *bin = malloc(DATA_SIZE);
    char *hex = malloc(DATA_SIZE*2);
    uint8_t *bin2 = malloc(DATA_SIZE);

    for(size_t i=0;i<DATA_SIZE;i++)
        bin[i] = rand();

    printf("data size = %d MB\n",(int)(DATA_SIZE/1024/1024));

    /* bin2hex */

    double t1 = now();

    for(int i=0;i<LOOPS;i++)
        bin2hex_fast(bin,DATA_SIZE,hex);

    double t2 = now();

    sink = hex[0];  // prevent optimizing away the loop
    printf("sink: %c\n",sink);

    double seconds = t2-t1;

    double throughput =
        ((double)DATA_SIZE*LOOPS)/(1024.0*1024.0*1024.0)/seconds;

    printf("bin2hex speed: %.2f GB/s\n",throughput);

    /* hex2bin */

    t1 = now();

    for(int i=0;i<LOOPS;i++)
        hex2bin_fast(hex,DATA_SIZE*2,bin2);

    t2 = now();

    sink = bin2[0];  // prevent optimizing away the loop
    printf("sink: %02X\n",sink);

    seconds = t2-t1;

    throughput =
        ((double)DATA_SIZE*LOOPS)/(1024.0*1024.0*1024.0)/seconds;

    printf("hex2bin speed: %.2f GB/s\n",throughput);

    free(bin);
    free(hex);
    free(bin2);



    return 0;
}
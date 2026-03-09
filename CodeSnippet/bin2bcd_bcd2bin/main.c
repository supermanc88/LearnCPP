#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


static const char hex_table[16] = {
    '0','1','2','3','4','5','6','7',
    '8','9','0','0','0','0','0','0'
};

size_t bcd2bin(const char *bcd, size_t bcd_len, char *out) {
    char *p = out;
    for (size_t i = 0; i < bcd_len; i++) {
        uint8_t v = bcd[i];
        *p++ = hex_table[v >> 4];
        *p++ = hex_table[v & 0x0F];
    }
    return p - out;
}


size_t bin2bcd(const char *in, size_t len, uint8_t *out) {
    size_t j = 0;

    for (size_t i = 0; i < len; i += 2) {
        uint8_t high = in[i] - '0';
        uint8_t low = (i + 1 < len) ? (in[i + 1] - '0') : 0;
        out[j++] = (high << 4) | low;
    }

    return j;
}


size_t bin2bcd_pad(
        const char *in,
        size_t len,
        uint8_t *out)
{
    size_t j = 0;
    size_t i = 0;

    if (len & 1)
    {
        out[j++] = (in[0] - '0');
        i = 1;
    }

    for (; i < len; i += 2)
    {
        uint8_t high = in[i] - '0';
        uint8_t low  = in[i+1] - '0';

        out[j++] = (high << 4) | low;
    }

    return j;
}


int main() {
    const char *bcd_data = "\x12\x34\x56\x78\x90";
    char bin_data[11];
    size_t bin_len = bcd2bin(bcd_data, 5, bin_data);
    bin_data[bin_len] = '\0';

    printf("BCD to BIN: %s\n", bin_data);

    uint8_t bcd_out[5];
    size_t bcd_len = bin2bcd(bin_data, bin_len, bcd_out);

    printf("BIN to BCD: ");
    for (size_t i = 0; i < bcd_len; i++) {
        printf("%02X ", bcd_out[i]);
    }
    printf("\n");


    const char *need_pad = "12345";
    size_t need_pad_len = 5;
    uint8_t bcd_pad_out[3];
    size_t bcd_pad_len = bin2bcd_pad(need_pad, need_pad_len, bcd_pad_out);
    printf("BIN to BCD with padding: ");
    for (size_t i = 0; i < bcd_pad_len; i++) {
        printf("%02X ", bcd_pad_out[i]);
    }
    printf("\n");

    return 0;
}
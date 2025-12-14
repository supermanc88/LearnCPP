#include <iostream>
#include <vector>
#include <unordered_map>

int test_vector() {
    std::vector<uint8_t> vec(5);

    std::cout << "Vector size: " << vec.size() << std::endl;


    vec.resize(10);
    std::cout << "Resized vector size: " << vec.size() << std::endl;

    vec.reserve(20);
    std::cout << "Reserved vector capacity: " << vec.capacity() << std::endl;
    std::cout << "Vector size after reserve: " << vec.size() << std::endl;
    return 0;
}


int test_unordered_map() {
    std::unordered_map<std::string, int> my_map;

    // add
    my_map["one"] = 1;
    my_map["two"] = 2;
    my_map["three"] = 3;
    my_map["four"] = 4;
    std::cout << "Map size after additions: " << my_map.size() << std::endl;

    // delete
    my_map.erase("one");
    std::cout << "Map size after deletion: " << my_map.size() << std::endl;

    // iterate
    for (const auto& [key, value] : my_map) {
        std::cout << key << ": " << value << std::endl;
    }

    // find
    auto it = my_map.find("two");
    if (it != my_map.end()) {
        std::cout << "Found key 'two' with value: " << it->second << std::endl;
    } else {
        std::cout << "Key 'two' not found." << std::endl;
    }

    it = my_map.find("one");
    if (it != my_map.end()) {
        std::cout << "Found key 'one' with value: " << it->second << std::endl;
    } else {
        std::cout << "Key 'one' not found." << std::endl;
    }

    // end
    auto end_it = my_map.end();
    std::cout << "End iterator points to: " << (end_it == my_map.end() ? "end" : "not end") << std::endl;


    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* 打印8字节Hex */
void print_hex(const char *title, const uint8_t *buf, int len) {
    printf("%s: ", title);
    for (int i = 0; i < len; i++)
        printf("%02X", buf[i]);
    printf("\n");
}

/* 左循环移位3位 */
static inline uint8_t rol3(uint8_t v) {
    return (uint8_t)((v << 3) | (v >> 5));
}

/*
 * derive_key_8
 * 输入8字节密钥 -> 输出8字节
 */
void derive_key_8(const uint8_t in[8], uint8_t out[8]) {
    uint8_t tmp1[8], tmp2[8], tmp3[8];

    /* Step 1 */
    tmp1[0] = in[0] + in[1];
    tmp1[1] = in[2] + in[3];
    tmp1[2] = in[4] + in[5];
    tmp1[3] = in[6] + in[7];

    tmp1[4] = in[0] ^ in[7];
    tmp1[5] = in[1] ^ in[6];
    tmp1[6] = in[2] ^ in[5];
    tmp1[7] = in[3] ^ in[4];

    /* Step 2 */
    tmp2[4] = tmp1[0] ^ tmp1[4];
    for (int i = 1; i < 4; i++)
        tmp2[i + 4] = tmp1[i + 4] ^ tmp2[4];

    /* Step 3 */
    tmp2[3] = tmp1[1] + tmp1[5];
    for (int i = 2; i >= 0; i--)
        tmp2[i] = tmp1[i] ^ tmp2[3];

    /* Step 4 */
    tmp3[0] = tmp2[0] ^ tmp2[2];
    tmp3[1] = tmp2[1] + tmp2[3];
    tmp3[2] = tmp2[4] ^ tmp2[6];
    tmp3[3] = tmp2[5] + tmp2[7];
    tmp3[4] = tmp2[0] ^ tmp2[1];
    tmp3[5] = tmp2[2] + tmp2[3];
    tmp3[6] = tmp2[4] ^ tmp2[5];
    tmp3[7] = tmp2[6] + tmp2[7];

    /* Step 5：循环左移3位 */
    for(int i=0;i<5;i++){
        out[i]=tmp3[i+3];
    }
    for(int i=5;i<8;i++){
        out[i]=tmp3[i-5];
    }
}

/*
 * 连续执行3次 derive_key_8
 */
void derive_key(const uint8_t in[8], uint8_t out[8]) {
    uint8_t tmp1[8], tmp2[8];

    derive_key_8(in, tmp1);
    derive_key_8(tmp1, tmp2);
    derive_key_8(tmp2, out);
}

/*
 * 示例：生成 LMK 对(00-01)
 */
void derive_lmk_pair(const uint8_t lmk[16], uint8_t out16[16]) {
    derive_key(lmk, out16);        // 前8字节
    derive_key(lmk + 8, out16 + 8); // 后8字节
}

/* 测试 */
int main() {
    // // 交行测试数据
    // uint8_t lmk[16] = {
    //     0x5e, 0x20, 0xd6, 0xd3, 0x10, 0xda, 0xce, 0xcd,
    //     0x70, 0x0b, 0x61, 0xda, 0x40, 0xf4, 0xb9, 0xef
    // };
    // uint8_t lmk[17] = "0101010101010101";

    // uint8_t lmk[16] = {
    //     0xc1, 0xc1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    //     0xd0, 0xd0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    // };
    //
    // char print_buf[256];
    //
    // uint8_t p[16];
    // memcpy(p, lmk, 16);
    //
    // for (int i = 0; i < 50; i++) {
    //     uint8_t result[16];
    //     derive_lmk_pair(p, result);
    //
    //     print_hex("Original LMK", p, 16);
    //
    //     sprintf(print_buf, "Derived LMK Pair (%d-%d)", i*2, i*2+1);
    //     print_hex(print_buf, result, 16);
    //     memcpy(p, result, 16);
    // }


    std::cout << "-1 & 1 = " << (-1 & 1) << std::endl;


    return 0;
}



// int main() {
//
//     // test_unordered_map();
//     return 0;
// }
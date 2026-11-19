// I wanted something that used a same size key //

#include <stdio.h>
#include <string.h>

void xor_cipher(unsigned char *data, size_t len,
                const unsigned char *key, size_t keylen) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % keylen];
    }
}

int main(void) {
    unsigned char msg[] = "HELLO";
    const unsigned char key[] = {0x9C, 0x2F, 0xE1, 0x07, 0x5B};  // 5 random bytes
    size_t len = strlen((char *)msg);

    xor_cipher(msg, len, key, sizeof(key));   // encrypt
    for (size_t i = 0; i < len; i++) printf("%02X ", msg[i]);
    printf("\n");

    xor_cipher(msg, len, key, sizeof(key));   // decrypt
    printf("%s\n", msg);
}

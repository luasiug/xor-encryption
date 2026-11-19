#include <stdio.h>
#include <string.h>

void xor_cipher(unsigned char* data, size_t len, const unsigned char* key,
                size_t keylen) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % keylen];  // flip bits where key has 1s
    }
}

int main(void) {
    unsigned char msg[] = "HELLO";
    const unsigned char key[] = "KEY";
    size_t len = strlen((char*)msg);

    xor_cipher(msg, len, key, 3);  // encrypt
    for (size_t i = 0; i < len; i++) printf("%02X ", msg[i]);
    printf("\n");

    xor_cipher(msg, len, key, 3);  // same call decrypts
    printf("%s\n", msg);           // HELLO
}

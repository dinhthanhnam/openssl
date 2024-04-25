#include <iostream>
#include <string>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

int encrypt(const unsigned char *text, int text_len, const unsigned char *key, unsigned char *cipher) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int cipher_len = 0;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL)) {
        std::cerr << "EVP_EncryptInit_ex() failed" << std::endl;
        return -1;
    }

    int len = 0;
    if (!EVP_EncryptUpdate(ctx, cipher, &len, text, text_len)) {
        std::cerr << "EVP_EncryptUpdate() failed" << std::endl;
        return -1;
    }
    cipher_len += len;

    if (!EVP_EncryptFinal_ex(ctx, cipher + len, &len)) {
        std::cerr << "EVP_EncryptFinal_ex() failed" << std::endl;
        return -1;
    }
    cipher_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return cipher_len;
}

int decrypt(const unsigned char *cipher, int cipher_len, const unsigned char *key, unsigned char *text) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int text_len = 0;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL)) {
        std::cerr << "EVP_DecryptInit_ex() failed" << std::endl;
        return -1;
    }

    int len = 0;
    if (!EVP_DecryptUpdate(ctx, text, &len, cipher, cipher_len)) {
        std::cerr << "EVP_DecryptUpdate() failed" << std::endl;
        return -1;
    }
    text_len += len;

    if (!EVP_DecryptFinal_ex(ctx, text + len, &len)) {
        std::cerr << "EVP_DecryptFinal_ex() failed" << std::endl;
        return -1;
    }
    text_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return text_len;
}

int main() {
    const unsigned char *key = (unsigned char*) "0123456789abcdef";
    const unsigned char *text = (unsigned char*) "toi yeu bav itde";
    unsigned char cipher[64], decrypted[64];

    int text_len = strlen((const char*)text);

    std::cout << "cipher = ";
    int cipher_len = encrypt(text, text_len, key, cipher);
    for (int i = 0; i < cipher_len; i++) {
        printf("%02x", cipher[i]);
    }
    std::cout << std::endl;

    std::cout << "decrypted = ";
    int dec_len = decrypt(cipher, cipher_len, key, decrypted);
    for (int i = 0; i < dec_len; i++) {
        std::cout << decrypted[i];
    }
    std::cout << std::endl;

    return 0;
}

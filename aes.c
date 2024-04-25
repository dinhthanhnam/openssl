#include <stdio.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <string.h>

int encrypt(const unsigned char *text, int text_len, const unsigned char *key, unsigned char *cipher) {
    int cipher_len = 0;
    int len = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, cipher, &len, text, text_len);
    cipher_len += len;
    EVP_EncryptFinal_ex(ctx, cipher + len, &len);
    cipher_len += len;
    EVP_CIPHER_CTX_free(ctx);

    return cipher_len;
}

int decrypt(const unsigned char *cipher, int cipher_len, const unsigned char *key, unsigned char *text) {
    int text_len = 0;
    int len = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, text, &len, cipher, cipher_len);
    text_len += len;
    EVP_DecryptFinal_ex(ctx, text + len, &len);
    text_len += len;
    EVP_CIPHER_CTX_free(ctx);

    return text_len;
}

int main() {
    const unsigned char *key = (unsigned char*) "0123456789abcdef";
    const unsigned char *text = (unsigned char*) "toi yeu bav itde";
    unsigned char cipher[64], decrypted[64];

    int text_len = strlen((const char*)text);

    printf("cipher = ");

    int cipher_len = encrypt(text, text_len, key, cipher);
    for (int i = 0; i < cipher_len; i++) {
        printf("%02x", cipher[i]);
    }
    printf("\n");

    printf("decrypted = ");

    int dec_len = decrypt(cipher, cipher_len, key, decrypted);
    for (int i = 0; i < dec_len; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}

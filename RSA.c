#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

// Sinh cặp khóa RSA và lưu vào file
int generateRSAKeyPair(const char *publicKeyFile, const char *privateKeyFile, int keySize) {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    FILE *publicKeyFilePtr = fopen(publicKeyFile, "wb");
    FILE *privateKeyFilePtr = fopen(privateKeyFile, "wb");

    if (!rsa || !bne || !publicKeyFilePtr || !privateKeyFilePtr) {
        perror("Error opening key files");
        return 0;
    }

    if (!BN_set_word(bne, RSA_F4) || !RSA_generate_key_ex(rsa, keySize, bne, NULL)) {
        perror("Error generating RSA key pair");
        return 0;
    }

    // Lưu khóa công khai
    if (!PEM_write_RSAPublicKey(publicKeyFilePtr, rsa)) {
        perror("Error writing public key");
        return 0;
    }

    // Lưu khóa riêng tư
    if (!PEM_write_RSAPrivateKey(privateKeyFilePtr, rsa, NULL, NULL, 0, NULL, NULL)) {
        perror("Error writing private key");
        return 0;
    }

    RSA_free(rsa);
    BN_free(bne);
    fclose(publicKeyFilePtr);
    fclose(privateKeyFilePtr);
    return 1;
}

// Mã hoá văn bản sử dụng khóa công khai RSA
char* rsaEncrypt(const char *plainText, RSA *rsaPublicKey) {
    int rsaLen = RSA_size(rsaPublicKey);
    char *cipherText = (char*)malloc(rsaLen);
    if (!cipherText) {
        perror("Memory allocation error");
        return NULL;
    }

    int cipherTextLen = RSA_public_encrypt(strlen(plainText) + 1, (const unsigned char*)plainText,
                                           (unsigned char*)cipherText, rsaPublicKey, RSA_PKCS1_PADDING);
    if (cipherTextLen == -1) {
        perror("Error encrypting message");
        free(cipherText);
        return NULL;
    }

    return cipherText;
}

// Giải mã văn bản sử dụng khóa riêng tư RSA
char* rsaDecrypt(const char *cipherText, RSA *rsaPrivateKey) {
    int rsaLen = RSA_size(rsaPrivateKey);
    char *plainText = (char*)malloc(rsaLen);
    if (!plainText) {
        perror("Memory allocation error");
        return NULL;
    }

    int plainTextLen = RSA_private_decrypt(rsaLen, (const unsigned char*)cipherText,
                                           (unsigned char*)plainText, rsaPrivateKey, RSA_PKCS1_PADDING);
    if (plainTextLen == -1) {
        perror("Error decrypting message");
        free(plainText);
        return NULL;
    }

    return plainText;
}

int main() {
    const char* publicKeyFile = "publickey.pem";
    const char* privateKeyFile = "privatekey.pem";
    const char* plainText = "Hello, world!";
    const int keySize = 2048;

    // Sinh cặp khóa RSA
    if (!generateRSAKeyPair(publicKeyFile, privateKeyFile, keySize)) {
        fprintf(stderr, "Error generating RSA key pair\n");
        return -1;
    }

    // Đọc khóa công khai từ file
    FILE *publicKeyFilePtr = fopen(publicKeyFile, "rb");
    if (!publicKeyFilePtr) {
        perror("Error opening public key file");
        return -1;
    }
    RSA *rsaPublicKey = PEM_read_RSAPublicKey(publicKeyFilePtr, NULL, NULL, NULL);
    fclose(publicKeyFilePtr);
    if (!rsaPublicKey) {
        perror("Error reading public key");
        return -1;
    }

    // Mã hoá văn bản
    char *encryptedText = rsaEncrypt(plainText, rsaPublicKey);
    if (!encryptedText) {
        fprintf(stderr, "Error encrypting message\n");
        RSA_free(rsaPublicKey);
        return -1;
    }

    printf("Encrypted text: %s\n", encryptedText);

    // Đọc khóa riêng tư từ file
    FILE *privateKeyFilePtr = fopen(privateKeyFile, "rb");
    if (!privateKeyFilePtr) {
        perror("Error opening private key file");
        return -1;
    }
    RSA *rsaPrivateKey = PEM_read_RSAPrivateKey(privateKeyFilePtr, NULL, NULL, NULL);
    fclose(privateKeyFilePtr);
    if (!rsaPrivateKey) {
        perror("Error reading private key");
        return -1;
    }

    // Giải mã văn bản
    char *decryptedText = rsaDecrypt(encryptedText, rsaPrivateKey);
    if (!decryptedText) {
        fprintf(stderr, "Error decrypting message\n");
        RSA_free(rsaPublicKey);
        RSA_free(rsaPrivateKey);
        free(encryptedText);
        return -1;
    }

    printf("Decrypted text: %s\n", decryptedText);

    // Giải phóng bộ nhớ
    RSA_free(rsaPublicKey);
    RSA_free(rsaPrivateKey);
    free(encryptedText);
    free(decryptedText);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string.h>

void sha256(const unsigned char *data, size_t len, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, len);
    EVP_DigestFinal_ex(mdctx, hash, &md_len);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    unsigned char data[] = "hello, world";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    sha256(data, strlen(data), hash);

    printf("SHA256 hash: ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    FILE *file = fopen("hashed.txt", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the hash to the file
    if (fwrite(hash, sizeof(unsigned char), SHA256_DIGEST_LENGTH, file) != SHA256_DIGEST_LENGTH) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("Hash written to file 'hashed.txt'\n");

    return 0;
}

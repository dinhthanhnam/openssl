#include<iostream>
#include<iomanip>
#include<openssl/sha.h>

bool simpleSHA256(void* input, unsigned long length, unsigned char* md)
{
    SHA256_CTX context;
    if (!SHA256_Init(&context))
        return false;

    if (!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if (!SHA256_Final(md, &context))
        return false;

    return true;
}

int main()
{
    std::string data = "Hello, World!"; // Sample data to hash

    unsigned char md[SHA256_DIGEST_LENGTH]; // 32 bytes

    if (!simpleSHA256((void*)data.c_str(), data.length(), md))
    {
        std::cerr << "Error hashing data\n";
        return 1;
    }

    // Print the hashed data
    std::cout << "SHA256 hash of \"" << data << "\":\n";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];
    }
    std::cout << std::endl;

    return 0;
}

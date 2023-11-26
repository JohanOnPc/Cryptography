#include "Crypto.h"

#include <iostream>
#include <format>

std::string cipher::caesar::encrypt(const std::string plainText)
{
    std::string cipherText;

    for (const auto& l : plainText)
    {
        cipherText += (l - 'a' + 3) % 26 + 'a';
    }

    return cipherText;
}

std::string cipher::caesar::decrypt(const std::string cipherText)
{
    std::string plainText;

    for (const auto& l : cipherText)
    {
        char l1 = (l - 'a' - 3) % 26;
        plainText += (l1 < 0) * 26 + l1 + 'a';
    }

    return plainText;
}

std::string cipher::vigenère::encrypt(const std::string plainText, const std::string key)
{
    const size_t keySize = key.size();
    size_t i = 0;
    std::string cipherText;

    for (const auto& l : plainText)
    {
        cipherText += (l + key[i++ % keySize] - 2 * 'a') % 26 + 'a';
    }

    return cipherText;
}

std::string cipher::vigenère::decrypt(const std::string cipherText, const std::string key)
{
    const size_t keySize = key.size();
    size_t i = 0;
    std::string plainText;

    for (const auto& l : cipherText)
    {
        char l1 = (l - key[i++ % keySize]) % 26;
        plainText += (l1 < 0) * 26 + l1 + 'a';
    }

    return plainText;
}

#define ROTATE(x, n) (x = (x << n | x >> (32 - n)));

void cipher::ChaCha20::ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d)
{
    a += b; d ^= a; ROTATE(d, 16);
    c += d; b ^= c; ROTATE(b, 12);
    a += b; d ^= a; ROTATE(d, 8);
    c += d; b ^= c; ROTATE(b, 7);
}

void cipher::ChaCha20::ChaCha20::InnerBlock()
{
    QuarterRound(element[0], element[4], element[8], element[12]);
    QuarterRound(element[1], element[5], element[9], element[13]);
    QuarterRound(element[2], element[6], element[10], element[14]);
    QuarterRound(element[3], element[7], element[11], element[15]);
    QuarterRound(element[0], element[5], element[10], element[15]);
    QuarterRound(element[1], element[6], element[11], element[12]);
    QuarterRound(element[2], element[7], element[8], element[13]);
    QuarterRound(element[3], element[4], element[9], element[14]);
}

void cipher::ChaCha20::ChaCha20::Block(uint32_t key[8], uint32_t counter, uint32_t nonce[3])
{
    class ChaCha20 workingState;
    element[0] = 0x61707865; element[1] = 0x3320646e; element[2] = 0x79622d32; element[3] = 0x6b206574;

    for (int i = 0; i < 8; i++)
        element[4 + i] = key[i];

    element[12] = counter; element[13] = nonce[0]; element[14] = nonce[1]; element[15] = nonce[2];

    workingState = *this;

    PrintState();

    for (int i = 0; i < 10; i++)
        InnerBlock();

    PrintState();

    for (int i = 0; i < 16; i++)
        element[i] += workingState[i];

    PrintState();
}

void cipher::ChaCha20::ChaCha20::PrintState()
{
    std::cout << std::format("{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n\n",
        element[0], element[1], element[2], element[3], element[4], element[5], element[6], element[7],
        element[8], element[9], element[10], element[11], element[12], element[13], element[14], element[15]);
}

void cipher::ChaCha20::PrintSerial(const ChaCha20& matrix)
{
    const std::byte* key_stream = reinterpret_cast<const std::byte*>(&matrix);
    for (int i = 0; i < 64; i++)
    {
        std::cout << std::format("{:02x} ", (unsigned char)key_stream[i]);
        if ((i + 1) % 16 == 0)
            std::cout << '\n';
    }
}

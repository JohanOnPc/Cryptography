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

void cipher::ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d)
{
    a += b; d ^= a; ROTATE(d, 16);
    c += d; b ^= c; ROTATE(b, 12);
    a += b; d ^= a; ROTATE(d, 8);
    c += d; b ^= c; ROTATE(b, 7);
}

void cipher::ChaCha20::InnerBlock(state& matrix)
{
    QuarterRound(matrix[0], matrix[4], matrix[8], matrix[12]);
    QuarterRound(matrix[1], matrix[5], matrix[9], matrix[13]);
    QuarterRound(matrix[2], matrix[6], matrix[10], matrix[14]);
    QuarterRound(matrix[3], matrix[7], matrix[11], matrix[15]);
    QuarterRound(matrix[0], matrix[5], matrix[10], matrix[15]);
    QuarterRound(matrix[1], matrix[6], matrix[11], matrix[12]);
    QuarterRound(matrix[2], matrix[7], matrix[8], matrix[13]);
    QuarterRound(matrix[3], matrix[4], matrix[9], matrix[14]);
}

uint32_t* cipher::ChaCha20::Block(uint32_t key[8], uint32_t counter, uint32_t nonce[3])
{
    struct state newState, workingState;
    newState[0] = 0x61707865; newState[1] = 0x3320646e; newState[2] = 0x79622d32; newState[3] = 0x6b206574;

    for (int i = 0; i < 8; i++)
        newState[4 + i] = key[i];

    newState[12] = counter; newState[13] = nonce[0]; newState[14] = nonce[1]; newState[15] = nonce[2];

    workingState = newState;

    PrintState(newState);

    for (int i = 0; i < 10; i++)
        InnerBlock(workingState);

    PrintState(workingState);

    for (int i = 0; i < 16; i++)
        newState[i] += workingState[i];

    PrintState(newState);

    return nullptr;
}

void cipher::ChaCha20::PrintState(state& matrix)
{
    std::cout << std::format("{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n{:08x} {:08x} {:08x} {:08x}\n\n",
        matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15]);
}

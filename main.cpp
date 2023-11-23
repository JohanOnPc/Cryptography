#include <iostream>
#include <bit>

#include "Crypto.h"

int main()
{
	std::string ciphertext = cipher::caesar::encrypt("theydrinkthetea");
	std::cout << ciphertext << " : " << cipher::caesar::decrypt(ciphertext) << "\n";

	ciphertext = cipher::vigenère::encrypt("theydrinkthetea", "duh");
	std::cout << ciphertext << " : " << cipher::vigenère::decrypt(ciphertext, "duh") << '\n';

	uint32_t a = 0x11111111, b = 0x01020304, c = 0x9b8d6f43, d = 0x01234567;

	cipher::ChaCha20::QuarterRound(a, b, c, d);

	std::cout << std::hex << a << ", " << b << ", " << c << ", " << d << '\n';

	uint32_t key[8] = { 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f, 0x10111213, 0x14151617, 0x18191a1b, 0x1c1d1e1f };
	uint32_t counter = 1;
	uint32_t nonce[3] = {0x00000009, 0x0000004a, 0x00000000};

	for (int i = 0; i < 8; i++)
	{
		key[i] = std::byteswap(key[i]);

		if (i < 3)
			nonce[i] = std::byteswap(nonce[i]);
	}


	cipher::ChaCha20::Block(key, counter, nonce);

	return 0;
}
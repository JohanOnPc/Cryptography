#include <iostream>
#include <bit>

#include "Crypto.h"
#include "BigInt.h"

void TestBigInt();

int main()
{
	std::string ciphertext = cipher::caesar::encrypt("theydrinkthetea");
	std::cout << ciphertext << " : " << cipher::caesar::decrypt(ciphertext) << "\n";

	ciphertext = cipher::vigenère::encrypt("theydrinkthetea", "duh");
	std::cout << ciphertext << " : " << cipher::vigenère::decrypt(ciphertext, "duh") << '\n';

	uint32_t a = 0x11111111, b = 0x01020304, c = 0x9b8d6f43, d = 0x01234567;	

	uint32_t key[8] = { 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c };
	uint32_t counter = 1;
	uint32_t nonce[3] = { 0x00000000, 0x4a000000, 0x00000000 };

	const char* PlainText = "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.";
	char* NewPlainText = new char[strlen(PlainText)];
	std::byte* CipherText = new std::byte[strlen(PlainText)];

	cipher::ChaCha20::Encrypt(reinterpret_cast<std::byte*>(key), counter, reinterpret_cast<std::byte*>(nonce), reinterpret_cast<const std::byte*>(PlainText), CipherText, strlen(PlainText) + 1);

	PrintBytes(CipherText, strlen(PlainText));

	cipher::ChaCha20::Encrypt(reinterpret_cast<std::byte*>(key), counter, reinterpret_cast<std::byte*>(nonce), CipherText, reinterpret_cast<std::byte*>(NewPlainText), strlen(PlainText) + 1);

	std::cout << NewPlainText << '\n';

	TestBigInt();

	return 0;
}

void TestBigInt()
{
	uint128 a{ 200000000000 }, b{ 1000000000000 };
	uint128 c = a * b;
	c = Divide(c, 1000);
	
	c = { 555555555555555 };
	c = c % 242342;
}
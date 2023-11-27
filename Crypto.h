#pragma once

#include <string>

namespace cipher
{
	namespace caesar
	{
		std::string encrypt(const std::string plainText);
		std::string decrypt(const std::string cipherText);
	}

	namespace vigenère
	{
		std::string encrypt(const std::string plainText, const std::string key);
		std::string decrypt(const std::string cipherText, const std::string key);
	}

	namespace ChaCha20
	{
		class ChaCha20
		{
			uint32_t element[16];

		public:

			uint32_t& operator[](size_t x) { return element[x]; }

			static void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
			void InnerBlock();
			void Block(uint32_t key[8], uint32_t counter, uint32_t nonce[3]);
			void PrintState();

		};

		void PrintSerial(const ChaCha20& matrix);
		void Encrypt(std::byte key[32], uint32_t counter, std::byte nonce[12], const std::byte* plainText, std::byte* cipherText, size_t length);
	}

	namespace poly1305
	{
		void Sign(std::byte key[32], const std::byte* message, size_t length, std::byte tag[16]);
	}
}

void PrintBytes(const std::byte* bytes, size_t length);

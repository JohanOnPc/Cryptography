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
		struct state
		{
			uint32_t element[16];

			uint32_t& operator[](size_t x) { return element[x]; }
		};

		void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
		void InnerBlock(state& matrix);
		uint32_t* Block(uint32_t key[8], uint32_t counter, uint32_t nonce[3]);

		void PrintState(state& matrix);
	}
}

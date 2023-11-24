#pragma once

#include <string>

namespace cipher
{
	namespace caesar
	{
		std::string encrypt(const std::string plainText);
		std::string decrypt(const std::string cipherText);
	}

	namespace vigen�re
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
			void Block(std::byte keyStream[64], uint32_t key[8], uint32_t counter, uint32_t nonce[3]);
			void Serialize(std::byte keyStream[64]);
			void PrintState();
		};

		void PrintSerial(std::byte keyStream[64]);
	}
}

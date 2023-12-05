#pragma once

#include <iostream>

class uint128
{
private:
	uint64_t num[2];

public:
	uint128(std::byte num[16]);
	uint128(uint64_t num[2]);
	uint128(uint64_t num);

	uint128 Add(uint128 a, uint128 b);
	uint128 Subtract(uint128 a, uint128 b);
	uint128 Multiply(uint128 a, uint128 b);

};

class uint256
{
private:
	
};


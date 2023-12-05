#include "BigInt.h"

uint128::uint128(std::byte num[16])
{
}

uint128::uint128(uint64_t num[2])
{
	this->num[0] = num[0];
	this->num[1] = num[1];
}

uint128::uint128(uint64_t num)
{
	this->num[0] = num;
	this->num[1] = 0;
}

uint128 uint128::Add(uint128 a, uint128 b)
{
	uint64_t num[2];
	num[0] = a.num[0] + b.num[0];
	num[1] = a.num[1] + b.num[1] + (num[0] < a.num[0] || num[0] < b.num[0]);

	return uint128(num);
}

uint128 uint128::Subtract(uint128 a, uint128 b)
{
	return uint128((uint64_t)0);
}

uint128 uint128::Multiply(uint128 a, uint128 b)
{
	uint64_t num[2];
	num[0] = a.num[0] & 0xffffffff * b.num[0] & 0xffffffff;
	num[0] += a.num[0] & 0xffffffff00000000 * b.num[0] & 0xffffffff;
	num[0] += a.num[0] & 0xffffffff * b.num[0] & 0xffffffff00000000;
	num[0] += ((a.num[0] & 0xffffffff00000000) >> 32 * (b.num[0] & 0xffffffff00000000) >> 32) << 32;
	
}

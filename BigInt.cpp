#include "BigInt.h"

#include <immintrin.h>

uint128::uint128(std::byte num[16])
{
	this->num[0] = std::byteswap(reinterpret_cast<uint64_t>(num));
	this->num[1] = std::byteswap(reinterpret_cast<uint64_t>(&num[8]));
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

uint128::uint128()
{
	this->num[0] = {};
	this->num[1] = {};
}

bool uint128::Get(size_t i) const
{
	if (i < 64)
		return num[0] >> i & 1;
	else if (i < 128)
		return num[1] >> (i - 64) & 1;

	throw std::out_of_range("Index is out of bounds");
}

void uint128::Set(size_t i, bool val)
{
	if (i < 64)
		num[0] = (num[0] & ~(static_cast<unsigned long long>(1) << i)) | (static_cast<unsigned long long>(val) << i);
	else if (i < 128)
		num[1] = (num[1] & ~(static_cast<unsigned long long>(1) << (i - 64))) | (static_cast<unsigned long long>(val) << (i - 64));
	else
		throw std::out_of_range("Index is out of bounds");
}

uint128 Add(const uint128 a, const uint128 b)
{
	uint64_t num[2] = {};
	num[0] = a.num[0] + b.num[0];
	num[1] = a.num[1] + b.num[1] + (num[0] < a.num[0] || num[0] < b.num[0]);

	return uint128(num);
}

uint128 Subtract(const uint128 a, const uint128 b)
{
	uint8_t borrow = {};
	uint128 ans;

	_subborrow_u64(borrow, a.num[0], b.num[0], &ans.num[0]);
	_subborrow_u64(borrow, a.num[1], b.num[1], &ans.num[1]);

	return ans;
}

uint128 Multiply(const uint128 a, const uint128 b)
{
	uint64_t num[2] = {};
	uint64_t ans;

	num[0] += (a.num[0] & 0xffffffff) * (b.num[0] & 0xffffffff);
	ans = (a.num[0] & 0xffffffff) * (b.num[0] >> 32); num[1] += (ans >> 32) + (((ans << 32) + num[0]) <= num[0]); num[0] += ans << 32;
	ans = (a.num[0] >> 32) * (b.num[0] & 0xffffffff); num[1] += (ans >> 32) + (((ans << 32) + num[0]) <= num[0]); num[0] += ans << 32;
	num[1] += (a.num[0] >> 32) * (b.num[0] >> 32);
	num[1] += (a.num[0] & 0xffffffff) * (b.num[1] & 0xffffffff);
	num[1] += (a.num[1] & 0xffffffff) * (b.num[0] & 0xffffffff);
	num[1] += ((a.num[0] & 0xffffffff) * (b.num[1] >> 32)) << 32;
	num[1] += ((a.num[1] >> 32) * (b.num[0] & 0xffffffff)) << 32;
	num[1] += ((a.num[0] >> 32) * (b.num[1] & 0xffffffff)) << 32;
	num[1] += (a.num[1] & 0xffffffff * (b.num[0] >> 32)) << 32;

	return uint128(num);
}

uint128 Divide(const uint128 a, const uint128 b)
{
	uint128 ans, rem;
	bool start = false;

	for (int i = 127; i >= 0; i--)
	{
		if (!start && a.Get(i))
			start = true;
		if (start)
		{
			rem = rem << 1;
			rem.Set(0, a.Get(i));

			if (rem >= b)
			{
				rem -= b;
				ans.Set(i, 1);
			}
		}
	}

	return ans;
}

uint128 operator+(const uint128 a, const uint128 b)
{
	return Add(a, b);
}

uint128& operator+=(uint128& a, const uint128 b)
{
	a = Add(a, b);
	return a;
}

uint128 operator-(const uint128 a, const uint128 b)
{
	return Subtract(a, b);
}

uint128& operator-=(uint128& a, const uint128 b)
{
	a = Subtract(a, b);
	return a;
}

uint128 operator*(const uint128 a, const uint128 b)
{
	return Multiply(a, b);
}

uint128& operator*=(uint128& a, const uint128 b)
{
	a = Multiply(a, b);
	return a;
}

uint128 operator/(const uint128 a, const uint128 b)
{
	return Divide(a, b);
}

uint128& operator/=(uint128& a, const uint128 b)
{
	a = Divide(a, b);
	return a;
}

uint128 operator%(const uint128 a, const uint128 b)
{
	uint128 ans;
	bool start = false;


	for (int i = 127; i >= 0; i--)
	{
		if (!start && a.Get(i))
			start = true;

		if (start)
		{
			ans = ans << 1;
			ans.Set(0, a.Get(i));
			if (ans >= b)
				ans -= b;
		}
	}

	return ans;
}

bool operator==(const uint128 a, const uint128 b)
{
	return a.num[0] == b.num[0] && a.num[1] == b.num[1];
}

bool operator!=(const uint128 a, const uint128 b)
{
	return !(a == b);
}

bool operator>(const uint128 a, const uint128 b)
{
	if (a.num[1] > b.num[1])
		return true;
	else if (a.num[1] < b.num[1])
		return false;
	else if (a.num[0] > b.num[0])
		return true;

	return false;
}

bool operator>=(const uint128 a, const uint128 b)
{
	if (a == b)
		return true;
	else
		return a > b;
}

bool operator<(const uint128 a, const uint128 b)
{
	return false;
}

bool operator<=(const uint128 a, const uint128 b)
{
	return false;
}

uint128 operator&(const uint128 a, const uint128 b)
{
	uint128 ans;
	ans.num[0] = a.num[0] & b.num[0];
	ans.num[1] = a.num[1] & b.num[1];
	return ans;
}

uint128 operator|(const uint128 a, const uint128 b)
{
	uint128 ans;
	ans.num[0] = a.num[0] | b.num[0];
	ans.num[1] = a.num[1] | b.num[1];
	return ans;
}

uint128 operator~(const uint128 a)
{
	uint128 ans;
	ans.num[0] = ~a.num[0];
	ans.num[1] = ~a.num[1];
	return ans;
}

uint128 operator^(const uint128 a, const uint128 b)
{
	uint128 ans;
	ans.num[0] = a.num[0] ^ b.num[0];
	ans.num[1] = a.num[1] ^ b.num[1];
	return ans;
}

uint128 operator>>(const uint128 a, size_t b)
{
	uint128 ans;
	ans.num[0] = a.num[0] >> b | a.num[1] << (64 - b);
	ans.num[1] = a.num[1] >> b;
	return ans;
}

uint128 operator<<(const uint128 a, size_t b)
{
	uint128 ans;
	ans.num[1] = a.num[1] << b | a.num[0] >> (64 - b);
	ans.num[0] = a.num[0] << b;
	return ans;
}

std::ostream& operator<<(std::ostream& os, const uint128 a)
{
	

	return os;
}


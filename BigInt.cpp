#include "BigInt.h"

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
	return false;
}

void uint128::Set(size_t i, bool val)
{
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
	return uint128((uint64_t)0);
}

uint128 Multiply(const uint128 a, const uint128 b)
{
	uint64_t num[2] = {};
	uint64_t ans;

	num[0] += a.num[0] & 0xffffffff * b.num[0] & 0xffffffff;
	ans = a.num[0] & 0xffffffff * (b.num[0] >> 32); num[0] += ans << 32; num[1] += ans >> 32;
	ans = (a.num[0] >> 32) * b.num[0] & 0xffffffff; num[0] += ans << 32; num[1] += ans >> 32;
	num[1] += (a.num[0] >> 32) * (b.num[0] >> 32);
	num[1] += a.num[0] & 0xffffffff * b.num[1] & 0xffffffff;
	num[1] += a.num[1] & 0xffffffff * b.num[0] & 0xffffffff;
	num[1] += (a.num[0] & 0xffffffff * (b.num[1] >> 32)) << 32;
	num[1] += ((a.num[1] >> 32) * b.num[0] & 0xffffffff) << 32;
	num[1] += ((a.num[0] >> 32) * b.num[1] & 0xffffffff) << 32;
	num[1] += (a.num[1] & 0xffffffff * (b.num[0] >> 32)) << 32;

	return uint128(num);
}

uint128 Divide(const uint128 a, const uint128 b)
{
	uint128 ans;


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
	return uint128();
}

uint128& operator/=(uint128& a, const uint128 b)
{
	// TODO: insert return statement here
}

uint128 operator%(const uint128 a, const uint128 b)
{
	uint128 ans;

	for (int i = 127; i >= 0; i--)
	{
		ans == ans << 1;
		ans.Set(0, a.Get(i));
		if (ans >= b)
			ans -= b;
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


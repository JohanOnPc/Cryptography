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
	uint128();

	bool Get(size_t i) const;
	void Set(size_t i, bool val);

	friend uint128 Add(const uint128 a, const uint128 b);
	friend uint128 Subtract(const uint128 a, const uint128 b);
	friend uint128 Multiply(const uint128 a, const uint128 b);
	friend uint128 Divide(const uint128 a, const uint128 b);

	friend uint128 operator+ (const uint128 a, const uint128 b);
	friend uint128& operator+= (uint128& a, const uint128 b);
	friend uint128 operator- (const uint128 a, const uint128 b);
	friend uint128& operator-= (uint128& a, const uint128 b);

	friend uint128 operator* (const uint128 a, const uint128 b);
	friend uint128& operator*= (uint128& a, const uint128 b);
	friend uint128 operator/ (const uint128 a, const uint128 b);
	friend uint128& operator/= (uint128& a, const uint128 b);
	friend uint128 operator% (const uint128 a, const uint128 b);

	friend bool operator== (const uint128 a, const uint128 b);
	friend bool operator!= (const uint128 a, const uint128 b);

	friend bool operator> (const uint128 a, const uint128 b);
	friend bool operator>= (const uint128 a, const uint128 b);
	friend bool operator< (const uint128 a, const uint128 b);
	friend bool operator<= (const uint128 a, const uint128 b);

	friend uint128 operator& (const uint128 a, const uint128 b);
	friend uint128 operator| (const uint128 a, const uint128 b);
	friend uint128 operator~ (const uint128 a);
	friend uint128 operator^ (const uint128 a, const uint128 b);

	friend uint128 operator>> (const uint128 a, size_t b);
	friend uint128 operator<< (const uint128 a, size_t b);




};

class uint256
{
private:
	
};


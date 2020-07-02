#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#define MAX_PRIME_VAL 0xfff

class RandomPrimeGenerator {
    bitset<MAX_PRIME_VAL> is_prime;
    // char is_prime[MAX_PRIME_VAL];
    long max;
    long prime;
public:
    RandomPrimeGenerator();
    RandomPrimeGenerator(long);
    void prime_sieve();
    void reset();
    long get_prime() const;
};

ostream& operator<<(ostream &, const RandomPrimeGenerator &);

class Base64 {
    static string base64_chars;
public:
    // TODO: make private
    static string encode(string);
    static string decode(string);

    static string encode_int8(vector<int> int_arr);
    static vector<int> decode_int8(string);

    static char get_b64_char(int);
};

#endif
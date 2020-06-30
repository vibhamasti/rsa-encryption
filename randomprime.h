#ifndef RANDOMPRIME_H
#define RANDOMPRIME_H

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

#endif
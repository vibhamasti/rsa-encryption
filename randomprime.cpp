#ifndef RANDOMPRIME_CPP
#define RANDOMPRIME_CPP

#include "randomprime.h"

#include <stdlib.h>
#include <iostream>

// Overloading cout operator
ostream& operator<<(ostream &out, const RandomPrimeGenerator &p) {
    out << p.get_prime();
    return out;
}

// Sieve of Eratosthenes to initialise array
void RandomPrimeGenerator::prime_sieve() {
    if (max > MAX_PRIME_VAL) max = MAX_PRIME_VAL;
    // Initialise 0 and 1
    is_prime[0] = is_prime[1] = 0;
    
    for (int i=2; i<max; ++i) {
        is_prime[i] = 1;
    }

    for (int i=2; i<max; ++i) {
        if (is_prime[i]) {
            // All multiples of i are non-prime
            for (int j=i*i; j<max; j+=i) {
                is_prime[j] = 0;
            }
        }
    }
}

RandomPrimeGenerator::RandomPrimeGenerator() {
    max = MAX_PRIME_VAL;
    // Initialise is_prime bitset
    prime_sieve();

    prime = rand() % max;
    while (!is_prime[prime]) {
        prime = rand() % max;
    }
}

RandomPrimeGenerator::RandomPrimeGenerator(long inp_max) {
    max = inp_max;
    // Initialise is_prime bitset
    prime_sieve();

    prime = rand() % max;
    while (!is_prime[prime]) {
        prime = rand() % max;
    }
}

void RandomPrimeGenerator::reset() {
    long same = prime;
    prime = rand() % max;
    while (!is_prime[prime] || prime==same) {
        prime = rand() % max;
    }
}

long RandomPrimeGenerator::get_prime() const{
    return prime;
}

#endif
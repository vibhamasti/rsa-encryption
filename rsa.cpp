#ifndef RSA_CPP
#define RSA_CPP

#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "rsa.h"

RSA::RSA() {

    // Initialise p and q as unique primes
    RandomPrimeGenerator prime_gen;
    p = prime_gen.get_prime();

    prime_gen.reset();

    q = prime_gen.get_prime();
    while (q == p) {
        prime_gen.reset();
        q = prime_gen.get_prime();
    }

    // Calculate n
    n = p*q;

    // Calculate phi
    phi = (p-1)*(q-1);

    // Make sure phi & e are coprime
    // Start with e as 3
    e = 3;
    while (!is_coprime(e, phi)) {
        ++e;
    }

    /* e*d mod phi = 1 */

    // Find d using extended Euclidean Algorithm
    
    /* 
    up_left             up_right
    down_left           down_right
    ------------------------------

    Columnar Euclidean Algorithm
    */
    long up_left = phi, up_right = phi;
    long down_left = e, down_right = 1;

    while (true) {
        
        long new_left = up_left - (up_left/down_left)*down_left;
        long new_right = up_right - (up_left/down_left)*down_right;

        while (new_left < 0) new_left += phi;
        while (new_right < 0) new_right += phi;

        if (new_left == 1) {
            d = new_right;

            // If d found is 0, reset
            if (d == 0) {
                do {
                    ++e;
                } while (!is_coprime(e, phi));
                up_left = phi;
                up_right = phi;
                down_left = e;
                down_right = 1;
            }
            else {
                break;
            }
        }

        up_left = down_left;
        up_right = down_right;

        down_left = new_left;
        down_right = new_right;
    }

}

// Recursive function to find gcd
long gcd(long large, long small) {
    if (small > large) {
        swap (large, small);
    }
    if (small != 0) {
        return gcd(small, large%small);
    }
    else {
        return large;
    }
}

// Function to tell if two numbers are coprime
bool is_coprime(long a, long b) {
    return (gcd(a, b) == 1);
}

#endif
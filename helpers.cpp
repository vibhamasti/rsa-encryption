#ifndef HELPERS_CPP
#define HELPERS_CPP

#include "helpers.h"

#include <stdlib.h>
#include <iostream>

// Initialise base64_chars
string Base64::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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


// Convert an ASCII message to base64
string Base64::encode(string ascii_message) {
    // Resultant string
    string result = "";

    // val stores the 24-bit chunks of the string
    int val = 0, no_of_bits = 0, padding = 0, b64_num =0;

    int str_len = ascii_message.length();

    for (int i=0; i<str_len; i+=3) {
        val = 0, no_of_bits = 0;

        // Read 3 chars at a time (24 bits)
        for (int j=i; ascii_message[j] && j<i+3; ++j) {
            // Shift val left 8 bits and add the next 8 bits
            val = val << 8;
            val = val | ascii_message[j];
            no_of_bits += 8;
        }

        // Number of '=' to append after the string
        padding = no_of_bits % 3;

        // Extract 6 bits at a time (4 chunks) to form base64
        while (no_of_bits) {
            // Find value of each block
            if (no_of_bits >= 6) {
                int bits_to_shift = no_of_bits - 6;
                // 63 is binary 111111
                b64_num = (val >> bits_to_shift) & 63;
                no_of_bits -= 6;
            }

            else {
                int bits_to_shift = 6 - no_of_bits;
                // 63 is binary 111111, append 0s to right
                b64_num = (val << bits_to_shift) & 63;
                no_of_bits = 0;
            }

            result += base64_chars[b64_num];

        }

    }

    // Padding
    for (int i=0; i<padding; ++i) {
        result += '=';
    }

    return result;
}

// Convert a base64 message back to ASCII
string Base64::decode(string b64_message) {
    string result = "";

    int str_len = b64_message.length();

    int no_of_bits = 0, val = 0, b64_index = 0;

    // Read 4 chars at a time (24 bits)
    for (int i=0; i<str_len ; i+=4) {
        no_of_bits = 0, val = 0;

        for (int j=i; b64_message[j] && j<i+4; ++j) {

            // If not a passing character
            if (b64_message[j] != '=') {
                // Make space for 6 bits
                val = val << 6;
                no_of_bits += 6;
                
                b64_index = base64_chars.find(b64_message[j]);
                if (b64_index == string::npos) {
                    cout << "error rip\n";
                }

                val = val | b64_index;
            
            }

            else if (b64_message[j] == '=') {
                val = val >> 2;
                no_of_bits -= 2;
            }

        }

        while (no_of_bits) {
            no_of_bits -= 8;

            // 255 in bin is 11111111, hex is 0xff
            result += (val >> no_of_bits) & 0xff;
        }

    }

    return result;
}



#endif
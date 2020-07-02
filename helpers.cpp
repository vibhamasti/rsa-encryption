#ifndef HELPERS_CPP
#define HELPERS_CPP

#include "helpers.h"

#include <stdlib.h>
#include <iostream>

// Initialise base64_chars
string Base64::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char Base64::get_b64_char(int index) {
    if (index >= base64_chars.length()) return 0;
    return base64_chars[index];
}

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

// Convert an int8 array to base64
string Base64::encode_int8(vector<int> int_arr) {
    // Resultant string
    string result = "";

    int len = int_arr.size();

    // val stores the 24-bit chunks of the string
    int val = 0, no_of_bits = 0, padding = 0, b64_num =0;


    for (int i=0; i<len; i+=3) {
        val = 0, no_of_bits = 0;

        // Read 3 chars at a time (24 bits)
        for (int j=i; int_arr[j] && j<i+3; ++j) {
            // Shift val left 8 bits and add the next 8 bits
            val = val << 8;
            val = val | int_arr[j];
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

// Convert base64 message to int8 array
vector<int> Base64::decode_int8(string b64_message) {
    vector<int> result;

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
            result.push_back((val >> no_of_bits) & 0xff);
        }

    }

    return result;
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


/* string Base64::dec_to_b64(long decimal) {
    string b64 = "";

    while (decimal) {
        // Six rightmost digits
        int index = decimal & 0x3f;
        b64 += base64_chars[index];
        decimal = decimal >> 6;
    }    

    reverse(b64.begin(), b64.end());
    return b64;
}

long Base64::b64_to_dec(string b64) {
    string decimal = "";

    long dec_num = 0;

    int b64_index = 0;

    for (int i=0; b64[i]; ++i) {
        b64_index = base64_chars.find(b64[i]);
        dec_num *= 64;
        dec_num += b64_index;
    }

    return dec_num;
}
 */
#endif
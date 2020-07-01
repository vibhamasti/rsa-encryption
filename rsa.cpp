#ifndef RSA_CPP
#define RSA_CPP

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "rsa.h"

RSA::RSA() {
    // Initialise base64_chars
    base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

// Helper recursive function to find gcd
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

// Helpter function to tell if two numbers are coprime
bool is_coprime(long a, long b) {
    return (gcd(a, b) == 1);
}

// Convert an ASCII message to base64
string RSA::b64_encode(string ascii_message) {
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
string RSA::b64_decode(string b64_message) {
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

// Function to encrypt a message using public key
string RSA::encrypt(string m) {
    string encrypted_message = "";

    for (int i=0; m[i]; ++i) {
        long m_num = m[i];

        long en_num = 1;

        /* m^e mod n */
        for (int j=0; j<e; ++j) {
            en_num = (en_num*m_num) % n;
        }

        encrypted_message += to_string(en_num) + string(" ");

    }

    return encrypted_message;    
}

// Function to decrypt an encrypter message using private key
string RSA::decrypt(string en_m) {
    string en_num_as_str = "";
    string decrypted_message = "";

    for (int i=0; en_m[i]; ++i) {

        // End of word
        if (en_m[i] == ' ') {
            long en_m_num = stol(en_num_as_str);
            en_num_as_str = "";

            long decr_num = 1;

            /* m^d mod n */
            for (int i=0; i<d; ++i) {
                decr_num = (decr_num*en_m_num) % n;
            }

            // Convert message back to str
            decrypted_message += (char) decr_num;

        }

        // Find 
        else {
            en_num_as_str += en_m[i];
        }

    }

    return decrypted_message;
}

#endif
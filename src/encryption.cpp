#ifndef ENCRYPTION_CPP
#define ENCRYPTION_CPP

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "encryption.h"

/* RC4 functions */

RC4::RC4(int inp_key[], int len) {

    key_len = len;
    is_gen = false;

    // Initialise key
    for (int i=0; i<key_len; ++i) {
        key[i] = inp_key[i];
    }

    // Initialise key stream
    for (int i=0; i<key_len; ++i) {
        key_stream[i] = 0;
    }

    // Populate S and K
    for (int i=0; i<CIPHER_LEN; ++i) {
        K[i] = key[i%key_len];
        S[i] = i;
    }
    key_schedule();
}

RC4::RC4() {
    do {
        key_len = rand()%CIPHER_LEN;
    } while (key_len < 2);
    
    is_gen = false;

    // Initialise key
    for (int i=0; i<key_len; ++i) {
        key[i] = rand()%CIPHER_LEN;
    }

    // Initialise key stream
    for (int i=0; i<key_len; ++i) {
        key_stream[i] = 0;
    }

    // Populate S and K
    for (int i=0; i<CIPHER_LEN; ++i) {
        K[i] = key[i%key_len];
        S[i] = i;
    }
    key_schedule();
}


void RC4::key_schedule() {
    int j = 0;
    // Key array K used to generate S array
    for (int i=0; i<CIPHER_LEN; ++i) {
        j = (S[i] + K[i]) % CIPHER_LEN;
        swap(S[i], S[j]);
    }
}

void RC4::stream_gen(string plaintext) {
    int i=0, j=0, k=0;
    int pt_len = plaintext.length();
    

    for (i=1; i<=pt_len; ++i) {
        j = (j + S[i]) % CIPHER_LEN;
        swap(S[i], S[j]);
        t = (S[i] + S[j]) % CIPHER_LEN;
        key_stream[k++] = S[t];
    }
    is_gen = true;
}

string RC4::encrypt(string plaintext) {
    if (!is_gen) {
        stream_gen(plaintext);
    }
    
    string ciphertext = "";
    vector<int> cipher_chars;

    for (int i=0; plaintext[i]; ++i) {
       cipher_chars.push_back((plaintext[i] ^ key_stream[i]));
    }

    ciphertext = Base64::encode_int8(cipher_chars);
    return ciphertext;
}

string RC4::decrypt(string ciphertext) {
    string plaintext = "";

    vector<int> cipher_chars = Base64::decode_int8(ciphertext);
    int len = cipher_chars.size();

    for (int i=0; i<len; ++i) {

        plaintext += (cipher_chars[i] ^ key_stream[i]);

    }
    return plaintext;
}

string RC4::get_key() {
    string key_str = "";

    // cout << "key inside function: ";
    for (int i=0; i<key_len; ++i) {
        /* string small_key = Base64::dec_to_b64(key[i]);
        if (small_key.length() == 1) {
            key_str += Base64::get_b64_char(0);
        } */
        // cout << key[i] << ' ';
        key_str += to_string(key[i]) + ' ';
    }
    // cout << endl;
    return key_str;
}

vector<int> RC4::get_key_arr() {
    vector<int> key_vector(key, key+key_len);
    return key_vector;
}


int RC4::get_len() {
    return key_len;
}

/* End of RC4 functions */


/* RSA functions */

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


// Function to encrypt a message using public key
// Shoulf return Base64 string
string RSA::encrypt(string m) {
    string encrypted_message = "";

    for (int i=0; m[i]; ++i) {
        long m_num = m[i];

        long en_num = 1;

        /* m^e mod n */
        for (int j=0; j<e; ++j) {
            en_num = (en_num*m_num) % n;
        }

        encrypted_message += to_string(en_num) + " ";
        // encrypted_message += Base64::dec_to_b64(en_num) + ' ';

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
            // long en_m_num = Base64::b64_to_dec(en_num_as_str);
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
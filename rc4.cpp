#ifndef RC4_CPP
#define RC4_CPP

#include "rc4.h"

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

#endif
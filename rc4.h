#ifndef RC4_H
#define RC4_H

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "helpers.h"

#define CIPHER_LEN 256

class RC4 {
    int S[CIPHER_LEN], K[CIPHER_LEN];
    int key[CIPHER_LEN], key_stream[CIPHER_LEN];
    int t, key_len;

    bool is_gen;

    // Helper functions
    void key_schedule();
    void stream_gen(string);

public:
    RC4();
    RC4(int [], int);
    string encrypt(string);
    string decrypt(string);

    // TODO: delete/modify
    int get_len();
    
    string get_key();
    vector<int> get_key_arr();
};

#endif
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "helpers.h"

using namespace std;

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

class RSA {
    long p, q, n, e, d, phi;
    string decrypt(string);         // Decrypts a message

public:
    RSA();

    string encrypt(string);         // Encrypts a message
    
    // TODO: delete function
    void print_stuff() {
        cout << "p: " << p << " q: " << q << endl;
        cout << "n: " << n << endl;
        cout << "e: " << e << " d: " << d << endl;
        cout << "phi: " << phi << endl;
    }
};


#endif
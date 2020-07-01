#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "randomprime.h"

using namespace std;

class RSA {
    long p, q, n, e, d, phi;

    string base64_chars;

public:
    RSA();
    
    // TODO: make private
    string b64_encode(string);
    string b64_decode(string);

    string encrypt(string);         // Encrypts a message
    string decrypt(string);         // Decrypts a message
    
    // TODO: delete function
    void print_stuff() {
        cout << "p: " << p << " q: " << q << endl;
        cout << "n: " << n << endl;
        cout << "e: " << e << " d: " << d << endl;
        cout << "phi: " << phi << endl;
    }
};

long gcd(long, long);
bool is_coprime(long, long);

#endif
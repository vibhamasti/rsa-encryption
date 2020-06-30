#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "randomprime.h"

using namespace std;

class RSA {
    long p, q, n, e, d, phi;

    public:
    RSA();
    long get_e();
    long get_n();
    
    void print_stuff() {
        cout << "p: " << p << " q: " << q << endl;
        cout << "n: " << n << endl;
        cout << "e: " << e << " d: " << d << endl;
        cout << "phi: " << phi << endl;
    }
};

long gcd (long, long);
bool is_coprime(long, long);

#endif
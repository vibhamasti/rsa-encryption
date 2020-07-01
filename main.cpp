#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <vector>

#include "rsa.h"
#include "rc4.h"
#include "randomprime.h"

using namespace std;



/* 
Text encryption using RSA
Steps:
1. Generate RSA values of e, n, d, p, q, phi
2. Ask for user to enter message
3. Encrypt the message and display
4. Decrypt the message and display
*/

/* 
Use RSA to encrypt the RC4 key
Use password for that
MH5??
*/

int main() {
    srand(time(0));

    RSA rsa_pair;
    //int key[] = {107, 101, 121};

    RC4 rc4_key;

    rsa_pair.print_stuff();

    string m;

    cout << "Enter message: ";

    // cin.ignore();
    getline(cin, m);

    // Base 64
    string b64 = rsa_pair.b64_encode(m);
    cout << "\nBase 64\n";
    cout << "Message in b64: " << b64 << endl;
    cout << "Message from b64 to ascii: " << rsa_pair.b64_decode(b64) << endl;


    // RSA
    string en = rsa_pair.encrypt(m);
    cout << "\nRSA\n";
    cout << "Message after encrption: " << rsa_pair.encrypt(m) << endl;
    cout << "Decrypted message: " << rsa_pair.decrypt(en) << endl;

    // RC4
    string rc4_en = rc4_key.encrypt(m);
    cout << "\nRC4\n";
    cout << "Message after encrption: " << rc4_en << endl;
    cout << "Decrypted message: " << rc4_key.decrypt(rc4_en) << endl;

    return 0;
}
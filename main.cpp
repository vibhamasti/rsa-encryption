#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <vector>

#include "rsa.h"
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
Use RC4 to encrypt the RSA key
Use password for that
MH5
*/

int main() {
    srand(time(0));

    RSA rsa_pair;

    rsa_pair.print_stuff();

    string m;

    cout << "Enter message: ";

    // cin.ignore();
    getline(cin, m);

    string en = rsa_pair.encrypt(m);

    cout << "Message after encrption: " << rsa_pair.encrypt(m) << endl;
    cout << "Decrypted message: " << rsa_pair.decrypt(en) << endl;

    return 0;
}
#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <vector>

#include "encryption.h"
#include "helpers.h"

using namespace std;



/* 
Text encryption using RSA
Steps:
1. Generate RSA values of e, n, d, p, q, phi
2. Ask for user to enter message
3. Encrypt the message and display
4. Decrypt the message and display
*/

int main() {
    srand(time(0));

    RSA rsa_pair;
    RC4 rc4_key;

    // rsa_pair.print_stuff();

    string m;

    cout << "Enter message: ";

    getline(cin, m);

    // RC4
    string rc4_en = rc4_key.encrypt(m);
    cout << "\nRC4\n";
    cout << "Message after encrption: " << rc4_en << endl;
    cout << "Decrypted message: " << rc4_key.decrypt(rc4_en) << endl;
    
    
    // string key = rc4_key.get_key();
    // cout << "key: " << key << endl;

    // Array of key numbers
    vector<int> key_vector = rc4_key.get_key_arr();

    // RC4 key for the message
    string key_b64 = Base64::encode_int8(key_vector);
    cout << "Key: " << key_b64 << endl;

    cout << endl;

    /* // Base 64
    string b64 = Base64::encode(m);
    cout << "\nBase 64\n";
    cout << "Message in b64: " << b64 << endl;
    cout << "Message from b64 to ascii: " << Base64::decode(b64) << endl; */


    // RSA
    string en_key = rsa_pair.encrypt(key_b64);
    cout << "\nRSA\n";
    cout << "Key after encrption: " << en_key << endl;
    // cout << "Key after encrption: " << Base64::encode(en_key) << endl;
    cout << "Decrypted key: " << rsa_pair.decrypt(en_key) << endl;

    // cout << endl << "int max: " << INT_MAX << endl;
    // cout << endl << "long max: " << LONG_MAX << endl;


    // cout << Base64::dec_to_b64(65) << endl;

    return 0;
}
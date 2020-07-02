#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <vector>

#include "rsa.h"
#include "rc4.h"
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

    // RSA rsa_pair;
    RC4 rc4_key;

    //rsa_pair.print_stuff();

    string m;

    cout << "Enter message: ";

    getline(cin, m);

    // RC4
    string rc4_en = rc4_key.encrypt(m);
    cout << "\nRC4\n";
    cout << "Message after encrption: " << rc4_en << endl;
    cout << "Decrypted message: " << rc4_key.decrypt(rc4_en) << endl;
    string key = rc4_key.get_key();
    cout << "key: " << key << endl;

    // Encode and decode key
    vector<int> key_vector = rc4_key.get_key_arr();

    string key_b64 = Base64::encode_int8(key_vector);
    cout << "Encoded key: " << key_b64 << endl;

    vector<int> decoded_b64 = Base64::decode_int8(key_b64);
    int len = decoded_b64.size();

    cout << "Decoded key: ";
    for (int i=0; i<len; ++i) {
        cout << decoded_b64[i] << " "; 
    }

    cout << endl;

    /* // Base 64
    string b64 = Base64::encode(m);
    cout << "\nBase 64\n";
    cout << "Message in b64: " << b64 << endl;
    cout << "Message from b64 to ascii: " << Base64::decode(b64) << endl; */


    // RSA
    /* string en_key = rsa_pair.encrypt(key);
    cout << "\nRSA\n";
    cout << "Key after encrption: " << en_key << endl;
    // cout << "Key after encrption: " << Base64::encode(en_key) << endl;
    cout << "Decrypted key: " << rsa_pair.decrypt(en_key) << endl;

    cout << endl << "char: " << (((char) 129) & 0xff)<< endl; */

    // cout << Base64::dec_to_b64(65) << endl;

    return 0;
}
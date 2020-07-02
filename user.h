#ifndef USER_H
#define USER_H

#include "encryption.h"

// TODO: store encrypted passwords
class User {
    string username, password;
    RSA rsa_used;
    RC4 rc4_used;
public:
    User();
    User(string, string);
};

#endif
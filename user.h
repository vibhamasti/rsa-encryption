#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

class UserHandler {
    fstream user_file;
    string file_name;
public:
    UserHandler(string);
    void create_user();
};

#endif
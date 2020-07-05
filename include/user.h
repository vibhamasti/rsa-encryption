#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "encryption.h"

#define MAX_LOGIN_ATTEMPTS 3

// TODO: store encrypted passwords
struct UserInfo {
    string username, password;
};

class User {
    UserInfo user_info;
    RSA rsa_used;
    RC4 rc4_used;
public:
    User();
    User(string, string);
    void view_messages();       // TODO
    void send_message(User, string);    // TODO
    UserInfo get_user_info();
};

class UserHandler {
    fstream user_file;
    string file_name;
public:
    UserHandler(string);
    void login_user();
    void create_user();
    void user_home(User);
    void send_message_verify(User);    // TODO
};


#endif
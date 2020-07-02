#ifndef USER_CPP
#define USER_CPP

#include "user.h"

User::User(string user, string passw) {
    username = user;
    password = passw;
    rsa_used.print_stuff();
}

UserHandler::UserHandler(string inp_file_name) {
    file_name = inp_file_name;

    user_file.open(file_name.c_str(), ios::in | ios::out);

    if (!user_file) {
        user_file.open(file_name.c_str(), ios::out);

        if (!user_file) {
            cout << "File creation failed.\n";
        }
        else {
            user_file.close();
        }
    }
    else {
        user_file.close();
    }
    
}

#endif
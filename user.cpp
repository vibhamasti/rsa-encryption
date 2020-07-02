#ifndef USER_CPP
#define USER_CPP

#include "user.h"

User::User(string user, string passw) {
    username = user;
    password = passw;
    rsa_used.print_stuff();
}



#endif
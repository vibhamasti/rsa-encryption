#ifndef USER_CPP
#define USER_CPP

#include "user.h"

User::User(string inp_username, string inp_password) {
    user_info.username = inp_username;
    user_info.password = inp_password;
    rsa_used.print_stuff();
}

UserHandler::UserHandler(string inp_file_name) {
    file_name = inp_file_name;

    // Create file if it doesn't exist
    user_file.open(file_name.c_str(), ios::binary | ios::in);

    if (!user_file) {
        user_file.open(file_name.c_str(), ios::binary | ios::out);
        // cout << "File creation failed.\n";

        if (!user_file) {
            cout << "File creation inside failed.\n";
        }
        else {
            user_file.close();
        }
    }
    else {
        user_file.close();
    }
    
}

void UserHandler::login_user() {
    string inp_username;
    cout << "Enter username: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);
    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }


    UserInfo temp;
    bool login_verified = false;

    while(user_file.read((char*) &temp, sizeof(temp))) {
        if (inp_username == temp.username) {
            login_verified = true;
            break;
        }
    }

    if (!login_verified) {
        cout << "User does not exist. Please create a user.\n";
        user_file.close();
        return;
    }


    // TODO: check password

    // Display messages of person
    cout << "Ready to check messages.\n";
    cout << temp.username << ' ' << temp.password << endl;
    user_file.close();
}

void UserHandler::create_user() {
    string inp_username, inp_password;
    cout << "Enter username: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);

    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }

    UserInfo temp;
    bool user_exists = false;

    while(user_file.read((char*) &temp, sizeof(temp))) {
        if (inp_username == temp.username) {
            user_exists = true;
            break;
        }
    }

    if (user_exists) {
        cout << "User already exists. Please login.\n";
        user_file.close();
        return;
    }

    user_file.close();
    fstream new_file;

    new_file.open("../users/new_file.dat", ios::binary | ios::out);
    user_file.open(file_name.c_str(), ios::binary | ios::in);

    cout << "Enter password: ";
    getline(cin, inp_password);

    while (user_file.read((char*) &temp, sizeof(temp))) {
        new_file.write((char*) &temp, sizeof(temp));
    }

    temp.username = inp_username;
    temp.password = inp_password;

    new_file.write((char*) &temp, sizeof(temp));

    new_file.close();
    user_file.close();

    remove(file_name.c_str());
    rename("../users/new_file.dat", file_name.c_str());

    cout << "User created successfully. Please login to view messages.\n";

}

#endif
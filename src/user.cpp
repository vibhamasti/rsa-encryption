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
    string inp_username, inp_password;
    UserInfo temp;
    bool login_verified = false;


    cout << "Enter username: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);
    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }

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

    login_verified = false;
    // TODO: encrypt password using mh5 hash
    for (int i=0; i<MAX_LOGIN_ATTEMPTS; ++i) {
        if (i && MAX_LOGIN_ATTEMPTS-i != 1) {
            cout << "\nWrong password. " << MAX_LOGIN_ATTEMPTS-i << " attempts remaining.\n";
        }
        else if (i && MAX_LOGIN_ATTEMPTS-i == 1) {
            cout << "\nWrong password. " << MAX_LOGIN_ATTEMPTS-i << " attempt remaining.\n";
        }
        cout << "Enter password: ";
        getline(cin, inp_password);
        if (inp_password == temp.password) {
            login_verified = true;
            break;
        }
    }

    if (!login_verified) {
        cout << "Login attempts exceeded.\n";
        return;
    }

    user_file.close();

    user_home(inp_username);
}

void UserHandler::create_user() {
    string inp_username, inp_password;
    UserInfo temp;
    bool user_exists = false;
    fstream new_file;
    string new_file_name = "users/new_file.dat";

    cout << "Enter username: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);

    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }

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
    

    new_file.open(new_file_name.c_str(), ios::binary | ios::out);
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
    rename(new_file_name.c_str(), file_name.c_str());

    cout << "User created successfully. Please login to view messages.\n";

}

void UserHandler::user_home(string inp_username) {
    int ch;
    char cont;

    do {
        cout << "Welcome to your profile, " << inp_username << endl;

        cout << "1. View all messages\n";
        cout << "2. Send a message\n";
        cout << "3. Back to main menu\n";

        cout << "\nYour choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1: {
                cout << "View messages!\n";
                break;
            }
            case 2: {
                cout << "Send messages!\n";
                break;
            }
            case 3: {
                return;
            }
            default: {
                cout << "Invalid choice.\n";
                continue;
            }
        }

        cout << "\nBack to user profile? (y/n): ";
        cin >> cont;

        if (tolower(cont) == 'n') break;

    } while (true);
    
}

#endif
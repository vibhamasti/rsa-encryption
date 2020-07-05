#ifndef USER_CPP
#define USER_CPP

#include "user.h"

User::User(string inp_username, string inp_password) {
    user_info.username = inp_username;
    user_info.password = inp_password;
    rsa_used.print_stuff();
}

User::User() {
    user_info.username = "";
    user_info.password = "";
}

UserInfo User::get_username() {
    return user_info.username;
}

UserInfo User::get_password() {
    return user_info.password;
}

void User::view_messages() {
    fstream message_file;
    string message, message_file_name, key_file_name;

    key_file_name = "messages/" + user_info.username + "-keys.txt";
    message_file_name = "messages/" + user_info.username + "-messages.txt";

    message_file.open(message_file_name, ios::in);


    if (!message_file) {
        cout << "No messages for you.\n";
        return;
    }

    // TODO: decrypt this
    while (getline(message_file, message)) {
        cout << message << endl;
    }
    message_file.close();
}

void User::send_message(User to_user, string message) {
    fstream to_message_file, new_message_file;
    string to_message_name, to_message_key;

    string copy_str;

    to_message_name = "messages/" + to_user.get_username() + "-messages.txt";
    to_message_key = "messages/" + to_user.get_username() + "-keys.txt";

    to_message_file.open(to_message_name.c_str(), ios::in);

    // If file already exists
    if (to_message_file) {
        new_message_file.open("messages/temp.txt", ios::out);

        while(getline(to_message_file, copy_str)) {
            new_message_file << copy_str << endl;
        }

        // TODO: encrypt this
        new_message_file << "From: " << user_info.username << endl;
        new_message_file << message << endl;

        new_message_file.close();
        to_message_file.close();

        remove(to_message_name.c_str());
        rename("messages/temp.txt", to_message_name.c_str());
    }

    // Otherwise create file
    else {
        to_message_file.open(to_message_name.c_str(), ios::out);

        // TODO: encrypt this
        to_message_file << "From: " << user_info.username << endl;
        to_message_file << message << endl;

        to_message_file.close();
    }

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
    User temp;
    bool login_verified = false;


    cout << "Enter username: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);
    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }

    while(user_file.read((char*) &temp, sizeof(temp))) {
        if (inp_username == temp.get_username()) {
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
        if (inp_password == temp.get_password()) {
            login_verified = true;
            break;
        }
    }

    if (!login_verified) {
        cout << "Login attempts exceeded.\n";
        user_file.close();
        return;
    }

    user_file.close();
    user_home(temp);
}

void UserHandler::create_user() {
    string inp_username, inp_password;
    User temp;
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
        if (inp_username == temp.get_username()) {
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
    
    // If user does not exist
    // TODO: generate RSA and RC4 keys

    new_file.open(new_file_name.c_str(), ios::binary | ios::out);
    user_file.open(file_name.c_str(), ios::binary | ios::in);

    cout << "Enter password: ";
    getline(cin, inp_password);

    User new_user(inp_username, inp_password);

    while (user_file.read((char*) &temp, sizeof(temp))) {
        new_file.write((char*) &temp, sizeof(temp));
    }

    new_file.write((char*) &new_user, sizeof(new_user));

    new_file.close();
    user_file.close();

    remove(file_name.c_str());
    rename(new_file_name.c_str(), file_name.c_str());

    cout << "User created successfully. Please login to view messages.\n";

}

void UserHandler::user_home(User temp) {
    int ch;
    char cont;

    do {
        cout << "Welcome to your profile, " << temp.get_username() << endl;

        cout << "1. View all messages\n";
        cout << "2. Send a message\n";
        cout << "3. Exit user profile\n";

        cout << "\nYour choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1: {
                cout << "View messages!\n";
                temp.view_messages();
                break;
            }
            case 2: {
                cout << "Send messages!\n";
                send_message_verify(temp);
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

void UserHandler::send_message_verify(User from_user) {
    string inp_username, temp_message;
    User temp;
    bool user_exists = false;
    int message_lines;
    stringstream message;

    cout << "Enter username of person you want to send message to: ";
    getline(cin, inp_username);

    user_file.open(file_name.c_str(), ios::binary | ios::in);
    if (!user_file) {
        cout << "File opening failed.\n";
        return;
    }

    while(user_file.read((char*) &temp, sizeof(temp))) {
        if (inp_username == temp.get_username()) {
            user_exists = true;
            // temp stores User information of the receiving user
            break;
        }
    }

    if (!user_exists) {
        cout << "User does not exist.\n";
        user_file.close();
        return;
    }

    user_file.close();

    // User exists, send message from User from_user to User temp
    cout << "Enter number of lines in message: ";
    cin >> message_lines;
    cin.ignore();

    for (int i=0; i<message_lines; ++i) {
        getline(cin, temp_message);
        message << temp_message << '\n';
    }

    // Send message
    from_user.send_message(temp, message.str());

}

#endif
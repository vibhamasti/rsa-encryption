#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>

#include <vector>

#include "encryption.h"
#include "helpers.h"
#include "user.h"

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

    UserHandler("users.txt");

    int ch;
    string cont = "";

    do {
        cout << "\nMAIN MENU\n\n";

        cout << "1. Create user\n";
        cout << "2. Login as user\n";
        cout << "3. Exit\n";

        cout << "\nYour choice: ";
        cin >> ch;

        switch (ch) {
            case 1:{
                cout << "You want to create a user\n";
                User("vibhamasti", "password");
                break;
            }

            case 2:{
                cout << "You want to login\n";
                break;
            }

            case 3:{
                return 0;
            }

            default: {
                cout << "Invalid choice.\n";
                continue;
            }
        }

        cout << "\nBack to main menu? (y/n): ";
        cin.ignore();
        getline(cin, cont);

        if (tolower(cont[0]) == 'n') break;

    } while(true);

    return 0;
}
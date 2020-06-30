#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <vector>

#include "rsa.h"
#include "randomprime.h"

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

    RSA rsa;

    rsa.print_stuff(); 

    return 0;
}
# text-encryption

A C++ based encryption service using RSA and RC4 encryption

## RSA Algorithm

RSA is an asymmetric cryptographic algorithm used to encrypt and decrypt messages. It uses a pair of keys (private and public) to cipher and decipher messages. The public key can be accessed by anyone whereas the private key is kept secret. The algorithm relies on the fact that finding prime factors of large numbers takes a very long time.

## RC4 Algorithm

## Program

In this program, users' private data will be encrypted and stored using RC4, and the symmetric key used for RC4 will be encrypted using RSA.

## Compile and execute

- To create an executable from the makefile, run `make -f mymake.mk`

- To execute the program, run `./a.out`

### Note
- After changing to Base64, not working properly; need to fix

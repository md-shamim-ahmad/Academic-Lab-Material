#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int main() {
    int p = 61; // Example prime number 1
    int q = 53; // Example prime number 2
    int e = 17; // Example public exponent

    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = modInverse(e, phi);

    // Message to be encrypted
    int plaintext;
    std::cout << "Enter a number to encrypt: ";
    std::cin >> plaintext;

    // Encryption: c = plaintext^e mod n
    int ciphertext = 1;
    for (int i = 0; i < e; ++i) {
        ciphertext = (ciphertext * plaintext) % n;
    }

    // Decryption: plaintext = c^d mod n
    int decryptedText = 1;
    for (int i = 0; i < d; ++i) {
        decryptedText = (decryptedText * ciphertext) % n;
    }

    std::cout << "Original message: " << plaintext << std::endl;
    std::cout << "Encrypted message: " << ciphertext << std::endl;
    std::cout << "Decrypted message: " << decryptedText << std::endl;

    return 0;
}

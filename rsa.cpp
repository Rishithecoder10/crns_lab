#include <iostream>
#include <cmath>
using namespace std;

// Function to find gcd
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse using Extended Euclidean Algorithm
int modInverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return -1; // No inverse
    if (t < 0) t += phi;
    return t;
}

// Function to perform modular exponentiation
int modPow(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to find suitable e
int findE(int phi) {
    for (int i = 2; i < phi; i++) {
        if (gcd(i, phi) == 1)
            return i;
    }
    return -1; // No valid e found (should not happen for valid primes)
}

int main() {
    // Choose two primes (small for simplicity)
    int p, q;
    cout << "Enter two prime numbers (e.g., 3 11): ";
    cin >> p >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = findE(phi); // Auto select e
    if (e == -1) {
        cout << "No valid 'e' found. Exiting." << endl;
        return 1;
    }

    int d = modInverse(e, phi);
    if (d == -1) {
        cout << "Modular inverse of e doesn't exist. Exiting." << endl;
        return 1;
    }

    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;

    // Encryption
    int plaintext;
    cout << "Enter plaintext number (integer): ";
    cin >> plaintext;

    int ciphertext = modPow(plaintext, e, n);
    cout << "Encrypted ciphertext: " << ciphertext << endl;

    // Decryption
    int decrypted = modPow(ciphertext, d, n);
    cout << "Decrypted plaintext: " << decrypted << endl;

    return 0;
}

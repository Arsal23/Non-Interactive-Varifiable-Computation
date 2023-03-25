#include<bits/stdc++.h>
using namespace std;

class MyClass {
public:
    bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to generate keys
void generate_keys(int &public_key, int &private_key) {
    // Generate two large random prime numbers
    int p = rand() % 900 + 100;
    while (!is_prime(p)) {
        p = rand() % 900 + 100;
    }
    int q = rand() % 900 + 100;
    while (!is_prime(q)) {
        q = rand() % 900 + 100;
    }

    // Calculate n and totient(n)
    int n = p * q;
    int totient = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < totient(n) and gcd(e, totient(n)) = 1
    int e = rand() % (totient - 1) + 2;
    while (gcd(e, totient) != 1) {
        e = rand() % (totient - 1) + 2;
    }

    // Calculate d such that d*e ≡ 1 mod totient(n)
    int d = 1;
    while ((d*e) % totient != 1) {
        d++;
    }

    // Set public and private keys
    public_key = n*e;
    private_key = d;

    // Write public and private keys to a file
    ofstream file("keys.txt");
    if (file.is_open()) {
        file << public_key << endl << private_key;
        file.close();
    }
}

// Function to encrypt a message using a public key
    int encrypt(int message, int public_key) {
        return (int)message*12 + 57;        //Affine cipher
    }

// Function to decrypt a message using a private key
    int run_output(int cipher_out, int private_key) {
        return (int)((cipher_out/6)-57)*0.5;
    }

    int func(int msg) {
        return (int)msg*6;
    }
}; 

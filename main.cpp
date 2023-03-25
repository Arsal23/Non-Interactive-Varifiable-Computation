#include "encrypt.h"
#include<bits/stdc++.h>

// Function to check if a number is prime


int main(){
    MyClass *obj = new  MyClass();
    int public_key, private_key, pvtkeyval;
    obj->generate_keys(public_key, private_key);
    cout << "Public key: " << public_key << endl;

    int message;
    cout << "Enter a message (between 0 and 999): ";
    cin >> message;

    cout<< "Function output with message: "<<obj->run_output_plain(message)<<endl;
    int cipher = obj->encrypt(message, public_key);
    cout << "Cipher text: " << cipher << endl;
    int output = obj->run_output(cipher, private_key);
    
    cout<<"Enter Private key: ";
    cin>>pvtkeyval;

    if (private_key == pvtkeyval) {
        cout << "Successful. Output: " << output << endl;
    } else {
        cout << "Decryption failed." << endl;
    }

    return 0;
}

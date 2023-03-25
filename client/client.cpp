#include<bits/stdc++.h>
#include "encrypt.h"
#include <sys/socket.h>
#include <arpa/inet.h> // added for inet_pton and htons
using namespace std;

int main(){
    int public_key, private_key, pvtkeyval;
    MyClass obj;
    obj.generate_keys(public_key, private_key);
    cout << "Public key: " << public_key << endl;

    int message;
    cout << "Enter a message (between 0 and 999): ";
    cin >> message;

    int plain_output = obj.func(message);
    //cout << "Function output with message: " << plain_output << endl;

    int cipher = obj.encrypt(message, public_key);
    // Encode the function and inputs into a string
    stringstream ss;
    ss << "encrypt " << cipher << " " << public_key;
    string encoded_input = ss.str();

    // Send the encoded input to the worker for evaluation
    // Assuming the worker's IP address is 192.168.1.2 and port number is 12345
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        cout << "Invalid address/ Address not supported" << endl;
        return 0;
    }
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "Connection Failed" << endl;
        return 0;
    }
    char buffer[1024] = {0};
    send(sockfd, encoded_input.c_str(), strlen(encoded_input.c_str()), 0);
    int valread = read(sockfd, buffer, 1024);

    // Decode the output received from the worker and verify it
    
    stringstream ss2(buffer);
    string command;
    ss2 >> command;
    if (command != "encrypt_output"){
        cout << "Error: Unexpected output received from the worker" << endl;
        return 0;
    }
    int cipher_out;
    ss2 >> cipher_out;


    cout << "Output recieved from server after applying function on it: " << cipher_out << endl;
	int output = obj.run_output(cipher_out, private_key);
    // Prompt user for private key input
    cout << "Enter Private key for decryption: ";
    cin >> pvtkeyval;

    if (private_key == pvtkeyval) {
    cout<<"Corect key....."<<endl;
                    cout<<"Short proof: c = a*6"<<endl;
        if (output == plain_output){
            cout << "Verification Successful. Answer: " <<output<< endl;
        } else {
            cout << "Verification Failed" <<output<<" "<<plain_output<< endl;
        }
    } else {
        cout << "Decryption failed." << endl;
    }

    close(sockfd); // Move close() here, after processing server's response

    return 0;
}


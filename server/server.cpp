#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
#include "encrypt.h"

using namespace std;

int main(){
    int port = 12345;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char encoded_output[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Wait for incoming connections and process them
    while(true){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }	
        cout << "Connection established" << endl;
        // Receive the encoded input from the client
        valread = read( new_socket , buffer, 1024);
        stringstream ss(buffer);
        string command;
        int cipher, public_key;
        ss >> command;
        if (command != "encrypt"){
            strcpy(encoded_output, "Error: Invalid command received");
        } else {
            ss >> cipher >> public_key;
            // Compute the result
            cout<<"cipher text recieved!"<<endl;
            MyClass obj;
            int cipher_out = obj.func(cipher);
            // Encode the output and send it back to the client
            stringstream ss2;
            ss2 << "encrypt_output " << cipher_out;
            cout<<"applying cypher text on function....."<<endl;
            cout<<"Cipher Output Sent!"<<endl;
            string encoded_output_str = ss2.str();
            strcpy(encoded_output, encoded_output_str.c_str());
            encoded_output[encoded_output_str.size()] = '\0'; // Add null terminator
        }
        send(new_socket, encoded_output, strlen(encoded_output) + 1, 0); // Include null terminator in length
        close(new_socket);
    }

    return 0;
}


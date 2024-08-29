#include <iostream>
#include <thread>
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>     
#include <unistd.h>        
#include <fstream>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1024;
const int PORT = 8080;
char directory[] = "./www";

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    
    recv(clientSocket, buffer, BUFFER_SIZE, 0);

    
    string request(buffer);
    char filename[256];
    strcpy(filename, directory);
    strcat(filename, "/index.html");

    if (request.find("GET /") == 0) {
        size_t start = 5; 
        size_t end = request.find(" ", start);
        string fileRequested = request.substr(start, end - start);
        if (fileRequested != "") {
            strcpy(filename, directory);
            strcat(filename, fileRequested.c_str());
        }
    }

    // Open the requested file
    ifstream file(filename);
    if (file.is_open()) {
        string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Connection: close\r\n\r\n";
        send(clientSocket, response.c_str(), response.size(), 0);

        string line;
        while (getline(file, line)) {
            line += "\n";
            send(clientSocket, line.c_str(), line.size(), 0);
        }
        file.close();
    } else {
        string response = "HTTP/1.1 404 Not Found\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Connection: close\r\n\r\n";
        response += "<html><body><h1>404 Not Found</h1></body></html>\n";
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    // Close the connection
    close(clientSocket);
}


int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Socket creation failed" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Binding failed" << endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) == -1) {
        cerr << "Listening failed" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Server started on port " << PORT << endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            cerr << "Failed to accept connection" << endl;
            continue;
        }

        // Create a new thread to handle the client connection
        thread clientThread(handleClient, clientSocket);
        clientThread.detach();  
        // Detach the thread to allow independent execution
    }

    close(serverSocket);
    return 0;
}
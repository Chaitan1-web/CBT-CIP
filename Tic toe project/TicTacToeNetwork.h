#ifndef TICTACTOENETWORK_H
#define TICTACTOENETWORK_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")  // Link with WinSock library

class TicTacToeNetwork {
private:
    SOCKET socketFD;             // Socket descriptor
    SOCKET connectionFD;         // Connection descriptor for client
    struct sockaddr_in serverAddr, clientAddr;  // Address structs
    int port;
    std::string ipAddress;

public:
    TicTacToeNetwork(std::string ip, int portNumber) : ipAddress(ip), port(portNumber) {}

    // Initialize WinSock
    void initializeWinSock() {
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            std::cerr << "WSAStartup failed with error: " << result << "\n";
            exit(1);
        }
    }

    // Start as a server
    void startServer() {
        initializeWinSock();

        // Create socket
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD == INVALID_SOCKET) {
            std::cerr << "Failed to create socket\n";
            WSACleanup();
            exit(1);
        }

        // Set up the server address
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        serverAddr.sin_port = htons(port);

        // Bind socket to IP and port
        if (bind(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Binding failed\n";
            closesocket(socketFD);
            WSACleanup();
            exit(1);
        }

        // Listen for incoming connections
        if (listen(socketFD, 1) == SOCKET_ERROR) {
            std::cerr << "Error listening on socket\n";
            closesocket(socketFD);
            WSACleanup();
            exit(1);
        }
    }

    // Accept client connection
    void acceptConnection() {
        int clientSize = sizeof(clientAddr);
        connectionFD = accept(socketFD, (struct sockaddr*)&clientAddr, &clientSize);
        if (connectionFD == INVALID_SOCKET) {
            std::cerr << "Error accepting connection\n";
            closesocket(socketFD);
            WSACleanup();
            exit(1);
        }
    }

    // Connect as a client
    void connectToServer() {
        initializeWinSock();

        // Create socket
        connectionFD = socket(AF_INET, SOCK_STREAM, 0);
        if (connectionFD == INVALID_SOCKET) {
            std::cerr << "Failed to create socket\n";
            WSACleanup();
            exit(1);
        }

        // Set up server address
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        serverAddr.sin_port = htons(port);

        // Connect to server
        if (connect(connectionFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Failed to connect to server\n";
            closesocket(connectionFD);
            WSACleanup();
            exit(1);
        }
    }

    // Send a move to the other player
    void sendMove(int row, int col) {
        int move[2] = {row, col};
        if (send(connectionFD, (char*)move, sizeof(move), 0) == SOCKET_ERROR) {
            std::cerr << "Failed to send move\n";
        }
    }

    // Receive a move from the other player
    void receiveMove(int &row, int &col) {
        int move[2];
        if (recv(connectionFD, (char*)move, sizeof(move), 0) == SOCKET_ERROR) {
            std::cerr << "Failed to receive move\n";
        }
        row = move[0];
        col = move[1];
    }

    // Close the socket and cleanup WinSock
    void closeConnection() {
        closesocket(connectionFD);
        closesocket(socketFD);
        WSACleanup();
    }
};

#endif

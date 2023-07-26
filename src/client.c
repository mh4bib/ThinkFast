#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <mcq_reader.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345

SOCKET client_socket;

int client(char** mail, int** level)
{
    WSADATA wsa;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        perror("WSAStartup failed");
        return 1;
    }

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        perror("Connection failed");
        return 1;
    }

    // Send an email to the server
    // const char* email = "hello@example.com";
    if (send(client_socket, *mail, strlen(*mail), 0) == SOCKET_ERROR)
    {
        perror("Email sending failed");
        closesocket(client_socket);
        return 1;
    }

    // Receive file destination from the server
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == SOCKET_ERROR || bytes_received == 0)
    {
        perror("File destination receiving failed");
        closesocket(client_socket);
        return 1;
    }
    buffer[bytes_received] = '\0';

    //Show quiz here
    int score = display_mcq(buffer, *mail, level, 1, 20);
    printf("You scored:%d\n", score);

    // Send the total score to the server
    sprintf(buffer, "%d", score);
    if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
    {
        perror("Number sending failed");
        closesocket(client_socket);
        return 1;
    }

    // Receive another number from the server
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == SOCKET_ERROR || bytes_received == 0)
    {
        perror("Number receiving failed");
        closesocket(client_socket);
        return 1;
    }
    buffer[bytes_received] = '\0';
    int number_from_server = atoi(buffer);
    printf("Received number: %d\n", number_from_server);

    // Close the socket and cleanup
    closesocket(client_socket);
    WSACleanup();

    return 0;
}

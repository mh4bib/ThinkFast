#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <mcq_reader.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

SOCKET client_socket;

int client(char** mail, int** level)
{
    WSADATA wsa;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];
    char time_limit_buffer[MAX_BUFFER_SIZE];

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

    // Receive time limit from the server
    bytes_received = recv(client_socket, time_limit_buffer, sizeof(time_limit_buffer), 0);
    if (bytes_received == SOCKET_ERROR || bytes_received == 0)
    {
        perror("Time limit receiving failed");
        closesocket(client_socket);
        return 1;
    }
    time_limit_buffer[bytes_received] = '\0';
    int time_limit = atoi(time_limit_buffer);
    printf("Time Limit Received: %d\n", time_limit);

    //Show quiz here
    int score = display_mcq(buffer, *mail, level, 1, time_limit);
    printf("You scored:%d\n", score);

    // Send the total score to the server
    sprintf(buffer, "%d", score);
    if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
    {
        perror("Number sending failed");
        closesocket(client_socket);
        return 1;
    }

    FILE* file = fopen("D:\\C-C++\\Projects\\ThinkFast\\database\\client_scores.txt", "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Write client_info to the file
    fprintf(file, "Email: %s, Total Score: %d\n", *mail, score);

    fclose(file);

    // Receive position from the server
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == SOCKET_ERROR || bytes_received == 0)
    {
        perror("Position receiving failed");
        closesocket(client_socket);
        return 1;
    }
    buffer[bytes_received] = '\0';
    int position = atoi(buffer);
    printf("Your position: %d\n", position);

    // Close the socket and cleanup
    closesocket(client_socket);
    WSACleanup();

    return 0;
}

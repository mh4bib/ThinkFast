#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345

int client(char** mail, int** level)
{
    WSADATA wsa;
    SOCKET client_socket;
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
    int score = display_mcq(buffer, *mail, level, 1);
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


/* 
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdbool.h>
#include <windows.h>
#include <process.h> // For _beginthreadex
#include<mcq_reader.h>
#include <login_prompt.h>
CONDITION_VARIABLE cv;
CRITICAL_SECTION cs;
#define PORT 8080
#define MAX_BUFFER_SIZE 1024

struct ThreadArgs {
    SOCKET client_socket;
    const char* filename;
    const char* email;
    const int** level;
};

 // Function to handle user input in a separate thread
unsigned __stdcall handleUserInput(void* args_ptr)
{
    struct ThreadArgs* args = (struct ThreadArgs*)args_ptr;
    SOCKET client_socket = args->client_socket;
    const char* filename = args->filename;
    const char* email = args->email;
    const int** level = args->level;

    // Print the filename and email received from the main thread
    printf("Filename: %s\n", filename);
    printf("Email: %s\n", email);
    printf("Level: %d\n", **level);

    char FileName[MAX_BUFFER_SIZE];
    strcpy(FileName, filename);
    FileName[strcspn(FileName, "\n")] = '\0';
    
    int score = display_mcq(FileName, email, level, 1);
    printf("You scored:%d\n", score);

    // send the score to the server
    //--------- ------ ----------


    
    char message[MAX_BUFFER_SIZE];
    while (1)
    {
        // Get user input
        printf("You: ");
        fflush(stdin);
        fgets(message, MAX_BUFFER_SIZE, stdin);

        // Remove the newline character from the message
        strtok(message, "\n");

        // Send the message to the server
        send(client_socket, message, strlen(message), 0);

        // Enter the critical section to wait for the signal from the main thread
        EnterCriticalSection(&cs);
        SleepConditionVariableCS(&cv, &cs, INFINITE);
    }

    return 0;
}

int client(char** mail, int** level)
{
    if (*mail == NULL)
    {
        printf("You're not logged in.Please login/register first\n");
        login_prompt(mail, level);
    }
    
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char email[50], server_reply[MAX_BUFFER_SIZE], filename[MAX_BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed to initialize Winsock");
        return 1;
    }

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Failed to create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address (localhost in this case)
    // server.sin_addr.s_addr = inet_addr("192.168.1.7");
    server.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Connection failed");
        return 1;
    }

    strcpy(email, *mail);
    email[strcspn(email, "\n")] = '\0'; // Remove the newline character from the email
     // Send the client email to the server
    send(client_socket, email, strlen(email), 0);
    printf("Connected to the server. Start typing messages...\n");

    // Receive the the filename from the server
    int bytes_received = recv(client_socket, filename, MAX_BUFFER_SIZE, 0);
    if (bytes_received == SOCKET_ERROR || bytes_received == 0)
    {
        printf("Server disconnected\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Null-terminate the received data to treat it as a string
    filename[bytes_received] = '\0';

    // Print the server's initial message
    printf("Filename: %s\n", filename);

    struct ThreadArgs args;
    args.client_socket = client_socket;
    args.filename = filename;
    args.email = email;
    args.level = level;

    // Create a separate thread to handle user input
    HANDLE userInputThread = (HANDLE)_beginthreadex(NULL, 0, handleUserInput, (void*)&args, 0, NULL);

    InitializeConditionVariable(&cv);
    InitializeCriticalSection(&cs);

    // Main thread will handle server communication
    while (1)
    {
        // Receive a reply from the server
        int bytes_received = recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0);
        if (bytes_received == SOCKET_ERROR || bytes_received == 0)
        {
            printf("Server disconnected\n");
            break;
        }

        // Null-terminate the received data to treat it as a string
        server_reply[bytes_received] = '\0';

        // Print the server's reply
        printf("Server: %s\n", server_reply);

        // Clear the buffer
        memset(server_reply, 0, sizeof(server_reply));

        // Signal the condition variable to wake up the user input thread
     WakeConditionVariable(&cv);
    }

    // Close the socket and cleanup
    closesocket(client_socket);
    WSACleanup();

    // Wait for the user input thread to finish
    WaitForSingleObject(userInputThread, INFINITE);
    CloseHandle(userInputThread);

    return 0;
}
 */
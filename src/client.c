#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdbool.h>
#include <windows.h>
#include <process.h> // For _beginthreadex
#include <login_prompt.h>
CONDITION_VARIABLE cv;
CRITICAL_SECTION cs;
#define PORT 8080
#define MAX_BUFFER_SIZE 1024

 // Function to handle user input in a separate thread
unsigned __stdcall handleUserInput(void* client_socket_ptr)
{
    SOCKET client_socket = *(SOCKET*)client_socket_ptr;
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
    char email[50], server_reply[MAX_BUFFER_SIZE];

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

    // Create a separate thread to handle user input
    HANDLE userInputThread = (HANDLE)_beginthreadex(NULL, 0, handleUserInput, (void*)&client_socket, 0, NULL);

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
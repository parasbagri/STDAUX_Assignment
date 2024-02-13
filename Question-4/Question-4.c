#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *html_response = "<h1>Hello from the simple web server!</h1>";

    // Create a socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Read the HTTP request
        valread = read(new_socket, buffer, 1024);
        printf("Received: %s\n", buffer);

        // Parse GET parameters (basic example)
        char *param_start = strstr(buffer, "?");
        char *param_value = param_start ? param_start + 1 : "";

        // Construct response
        char response[1024];
        sprintf(response, "<h1>Parameters: %s</h1>", param_value);
        strcat(response, html_response);

        // Send the response
        send(new_socket, response, strlen(response), 0);
        printf("Response sent\n");

        // Close the connection
        close(new_socket);
    }

    return 0;
}
/* ====================================================================
Compilation and Execution:

Save the code as webserver.c.
Compile with: gcc webserver.c -o webserver
Run: ./webserver
Access in a 
web browser: http://localhost:8080 (or http://localhost:8080?param1=value1&param2=value2 to test parameters)


Key Points:

Uses socket programming for network communication.
Handles basic HTTP GET requests.
Parses GET parameters for basic dynamic content.
Sends an HTML response with the parsed parameters.
Can be expanded with more request handling and response generation.

 */
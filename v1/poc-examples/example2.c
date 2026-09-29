
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // create socket
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // prepare server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9000);
    
    // bind socket to server address
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    
    // start listening for clients
    listen(server_socket, 5);
    printf("Server is listening on port 9000\n");
    
    // accept client connections
    socklen_t client_address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
    printf("Client connected from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    
    // loop to receive and respond to client requests
    while (1) {
        // receive request from client
        uint8_t buffer[1024];
        int request_size = recv(client_socket, buffer, sizeof(buffer), 0);
        
        // parse TLV request
        uint8_t tag = buffer[0];
        uint16_t length = (buffer[1] << 8) | buffer[2];
        uint8_t *value = &buffer[3];
        printf("Received request, tag=%d, length=%d, value=%s\n", tag, length, value);
        
        // create TLV response
        uint8_t response_buffer[1024];
        response_buffer[0] = tag;
        response_buffer[1] = length;
        memcpy(&response_buffer[2], value, length);
        
        // send response to client
        int response_size = send(client_socket, response_buffer, length + 2, 0);
        printf("Sent response, size=%d\n", response_size);
    }
    
    // close sockets
    close(client_socket);
    close(server_socket);
    
    return 0;
}

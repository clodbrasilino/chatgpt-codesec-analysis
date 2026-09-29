#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define SERVER_PORT 80
#define WEB_ROOT "/var/www/html/"

int main(int argc, char *argv[]) {
    int sockfd, new_sockfd, port_number, web_root_len;
    socklen_t client_len;
    char buffer[4096];
    struct sockaddr_in server_address, client_address;

    // Create TCP/IP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set server address
    bzero((char *) &server_address, sizeof(server_address));
    port_number = SERVER_PORT;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_number);

    // Bind socket to local address
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket to address");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Server is listening on port %d\n", port_number);
    web_root_len = strlen(WEB_ROOT);

    while (1) {
        // Accept incoming connection
        client_len = sizeof(client_address);
        new_sockfd = accept(sockfd, (struct sockaddr *) &client_address, &client_len);
        if (new_sockfd < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        // Read HTTP request from client
        bzero(buffer, 4096);
        read(new_sockfd, buffer, 4095);

        // Parse HTTP request (assume it is a GET request)
        char *filename = strtok(buffer + 4, " "); 
        if (strcmp(filename, "/") == 0) {
            filename = "/index.html";
        }
        char *path = malloc(web_root_len + strlen(filename) + 1);
        path[0] = '\0';
        strcat(path, WEB_ROOT);
        strcat(path, filename);
        // Vulnerable code here? WEB_ROOT is /var/www/html, what if you pass ../../../etc/passwd?
        // in my computer, var points to /private/var, so i successfully ran ../../../../etc/passwd

        // Serve HTTP response
        FILE *file = fopen(path, "rb");
        if (file == NULL) {
            char *not_found_response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "\r\n"
                "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>\r\n";
            write(new_sockfd, not_found_response, strlen(not_found_response));
        } else {
            char *ok_response_header =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "\r\n";
            write(new_sockfd, ok_response_header, strlen(ok_response_header));
            while (1) {
                int bytes_read = fread(buffer, 1, 4096, file);
                if (bytes_read == 0) {
                    break;
                }
                write(new_sockfd, buffer, bytes_read);
            }
            fclose(file);
        }

        // Close connection
        close(new_sockfd);
        free(path);
    }

    return 0;
}

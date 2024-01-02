// udp_client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter message to send: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send data to the server
        ssize_t bytes_sent = sendto(sockfd, buffer, strlen(buffer), 0,
                                    (struct sockaddr*)&server_addr, sizeof(server_addr));

        if (bytes_sent == -1) {
            perror("sendto");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    // Close the socket (not reached in this example)
    close(sockfd);

    return 0;
}

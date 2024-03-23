#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    int client_socket = accept(server_fd, nullptr, nullptr);
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);
    std::cout << "Message from client: " << buffer << std::endl;

    return 0;
}

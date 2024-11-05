#include <iostream>
#include <string.h> // for memset
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_addr
#include <unistd.h> // for close

#define PORT 65432
#define MAX_CLIENTS 5

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *message = "Message received!";

    // 创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    // 绑定socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    // 监听连接请求
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        return -1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // 接受连接请求
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        return -1;
    }

    std::cout << "Connected to client" << std::endl;

    // 读取客户端消息
    int valread = read(new_socket, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    // 发送响应消息
    send(new_socket, message, strlen(message), 0);
    std::cout << "Message sent to client" << std::endl;

    // 关闭连接
    close(new_socket);
    close(server_fd);

    return 0;
}

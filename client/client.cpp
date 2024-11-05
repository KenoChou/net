#include <iostream>
#include <string.h> // for memset
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_addr
#include <unistd.h> // for close

#define PORT 65432
#define SERVER_IP "127.0.0.1"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello, Server!";

    // 创建socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IP地址从字符串转换为网络字节序
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    // 发送消息
    send(sock, message, strlen(message), 0);
    std::cout << "Message sent to server" << std::endl;

    // 读取服务器响应
    int valread = read(sock, buffer, 1024);
    std::cout << "Received from server: " << buffer << std::endl;

    // 关闭连接
    close(sock);

    return 0;
}

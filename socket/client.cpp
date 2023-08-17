#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int sockFd;
    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8889);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockFd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    char buf[] = {"hello"};

    write(sockFd, buf, sizeof(buf));

    return 0;
}
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
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockFd, (sockaddr*)&addr, sizeof(sockaddr));

    listen(sockFd, 4);

    while (1) {
        sockaddr_in addrCli;
        int         sockCli;

        socklen_t cliLen = sizeof(addrCli);

        sockCli = accept(sockFd, (sockaddr*)&addrCli, &cliLen);
        while (1) {
            char buffer[1024] = {0};
            int  len          = read(sockCli, buffer, 1024);
            if (len < 0) {
                perror("recv");
                continue;
            } else if(len > 0){
                buffer[len] = '\0';
                printf("%drecv data is %s\n", len, buffer);
            }
        }
    }
    return 0;
}
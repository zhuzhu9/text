#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int lfd;
    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bool bReuseaddr = true;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(bReuseaddr));

    sockaddr_in addr, caddr;
    bzero(&addr, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(8888);

    bind(lfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(lfd, 128);

    pollfd client[1024];
    char   buf[1024];

    client[0].fd     = lfd;
    client[0].events = POLLIN;

    for (int i = 1; i < 1024; ++i) {
        client[i].fd = -1;
    }

    int maxfd = 0;

    while (true) {
        int res = poll(client, maxfd + 1, -1);
        if (client[0].revents == POLLIN) {
            int       cfd  = -1;
            socklen_t clen = sizeof(caddr);
            cfd            = accept(lfd, reinterpret_cast<sockaddr*>(&caddr), &clen);

            printf("ip %s, port %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
            for (int i = 1; i < 1024; ++i) {
                if (client[i].fd == -1) {
                    client[i].fd     = cfd;
                    client[i].events = POLLIN;
                    if (i > maxfd) maxfd = i;
                    break;
                }
            }

            if (res == 1) continue;
        }

        for (int i = 1; i <= maxfd; ++i) {
            if (client[i].fd < 0) continue;
            if (client[i].revents == POLLIN) {
                memset(buf, 0, sizeof(buf));
                int n = read(client[i].fd, buf, 1024);
                if (n == 0) {
                    close(client[i].fd);
                    client[i].fd = -1;
                } else if (n > 0) {
                    for (int j = 0; j < n; ++j) {
                        buf[j] = toupper(buf[j]);
                    }
                    send(client[i].fd, buf, n, 0);
                } else {
                    if (errno == ECONNRESET) {
                        close(client[i].fd);
                        client[i].fd = -1;
                    }
                }
                if (res == 1) break;
            }
        }
    }
    return 0;
}
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int lfd;
    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bool opt = true;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(8888);

    bind(lfd, (sockaddr*)&addr, sizeof(addr));
    listen(lfd, 128);

    int epoll_root = epoll_create(5000);

    epoll_event lev;
    lev.events  = EPOLLIN;
    lev.data.fd = lfd;
    epoll_ctl(epoll_root, EPOLL_CTL_ADD, lfd, &lev);

    epoll_event ep_ev[1000];
    char        buf[1024];

    while (true) {
        int res = epoll_wait(epoll_root, ep_ev, 1000, -1);
        for (int i = 0; i < res; ++i) {
            if (ep_ev[i].data.fd == lfd) {
                int         cfd;
                sockaddr_in caddr;
                socklen_t   clen = sizeof(caddr);
                cfd              = accept(lfd, (sockaddr*)&caddr, &clen);

                printf("ip %s, port %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

                epoll_event temp;
                temp.events  = EPOLLIN;
                temp.data.fd = cfd;
                epoll_ctl(epoll_root, EPOLL_CTL_ADD, cfd, &temp);
            } else {
                memset(buf, 0, sizeof(buf));
                int n = read(ep_ev[i].data.fd, buf, sizeof(buf));
                if (n == 0) {
                    close(ep_ev[i].data.fd);
                    epoll_ctl(epoll_root, EPOLL_CTL_DEL, ep_ev[i].data.fd, nullptr);
                } else if (n > 0) {
                    for (int j = 0; j < n; ++j) {
                        buf[j] = toupper(buf[j]);
                    }
                    send(ep_ev[i].data.fd, buf, n, 0);
                } else {
                    if (errno == ECONNRESET) {
                        close(ep_ev[i].data.fd);
                        epoll_ctl(epoll_root, EPOLL_CTL_DEL, ep_ev[i].data.fd, nullptr);
                    }
                }
            }
        }
    }

    return 0;
}
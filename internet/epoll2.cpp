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
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(8889);

    bind(lfd, (sockaddr*)&addr, sizeof(addr));

    listen(lfd, 128);

    int ep = epoll_create(1024);

    epoll_event ev, ep_ev[1024];
    ev.data.fd = lfd;
    ev.events  = EPOLLIN;

    char buf[1024];

    epoll_ctl(ep, EPOLL_CTL_ADD, lfd, &ev);

    while (true) {
        int ret = epoll_wait(ep, ep_ev, 1024, -1);

        for (int i = 0; i < ret; ++i) {
            if (ep_ev[i].data.fd == lfd) {
                int         cfd;
                sockaddr_in caddr;
                socklen_t   len = sizeof(caddr);
                cfd             = accept(lfd, (sockaddr*)&caddr, &len);
                std::printf("ip: %s, port: %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

                ev.data.fd = cfd;
                ev.events  = EPOLLIN;
                epoll_ctl(ep, EPOLL_CTL_ADD, cfd, &ev);
            } else {
                bzero(buf, sizeof(buf));
                int len = recv(ep_ev[i].data.fd, buf, 1024, 0);
                if (len > 0) {
                    for (int j = 0; j < len; ++j) {
                        buf[j] = toupper(buf[j]);
                    }
                    send(ep_ev[i].data.fd, buf, len, 0);
                } else if (len == 0) {
                    close(ep_ev[i].data.fd);
                    epoll_ctl(ep, EPOLL_CTL_DEL, ep_ev[i].data.fd, nullptr);
                } else {
                    if (errno == ECONNRESET) {
                        close(ep_ev[i].data.fd);
                        epoll_ctl(ep, EPOLL_CTL_DEL, ep_ev[i].data.fd, nullptr);
                    }
                }
            }
        }
    }
    return 0;
}
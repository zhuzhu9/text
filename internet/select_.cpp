#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void connection() {
    int lfd = -1;
    lfd     = socket(AF_INET, SOCK_STREAM, 0);

    bool bReuseaddr = true;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(bReuseaddr));

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_port        = htons(8888);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family      = AF_INET;

    bind(lfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(lfd, 128);

    fd_set set, all_set;
    FD_ZERO(&set);
    FD_SET(lfd, &set);

    char buf[4096];
    int  maxfd = lfd;

    while (1) {
        all_set = set;
        int ret = select(maxfd + 1, &all_set, nullptr, nullptr, nullptr);
        if (ret > 0) {
            if (FD_ISSET(lfd, &all_set)) {
                struct sockaddr_in caddr;
                socklen_t          clen = sizeof(caddr);
                int                cfd  = accept(lfd, (struct sockaddr*)&caddr, &clen);
                printf("ip %s, port %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
                FD_SET(cfd, &set);

                if (cfd > maxfd) maxfd = cfd;

                if (ret == 1) continue;
            }
        }

        for (int i = lfd; i <= maxfd; ++i) {
            if (FD_ISSET(i, &all_set)) {
                memset(buf, 0, sizeof(buf));
                int n = read(i, buf, sizeof(buf));
                if (n == 0) {
                    close(i);
                    FD_CLR(i, &set);
                } else if (n > 0) {
                    for (int j = 0; j < n; ++j) {
                        buf[j] = toupper((int)(buf[j]));
                    }
                    send(i, buf, n, 0);
                }
                if (ret == 1) break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    connection();
    return 0;
}
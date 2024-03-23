#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return -1;
    }

    if (cpid == 0) {  // 子进程
        close(pipefd[1]);  // 关闭写端
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        close(pipefd[0]);
        _exit(0);
    } else {  // 父进程
        close(pipefd[0]);  // 关闭读端
        write(pipefd[1], "Hello, World!\n", 14);
        close(pipefd[1]);
        wait(nullptr);  // 等待子进程
    }

    return 0;
}

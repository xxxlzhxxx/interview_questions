#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    message msg;
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from Message Queue!");

    msgsnd(msgid, &msg, sizeof(msg), 0);
    std::cout << "Sent message: " << msg.mtext << std::endl;

    return 0;
}

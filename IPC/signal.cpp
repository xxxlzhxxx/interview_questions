#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("semfile", 65);
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    semun sem_union;
    sem_union.val = 1;
    semctl(semid, 0, SETVAL, sem_union);

    std::cout << "Semaphore created." << std::endl;

    return 0;
}

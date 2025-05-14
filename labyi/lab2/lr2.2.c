#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/sched.h>
#include <string.h>

int main(void) {
    char smsg[20];
    char rmsg[200];
    int coid;
    long serv_pid;
    struct sched_param param;

    // Устанавливаем приоритет и алгоритм планирования (RR)
    param.sched_priority = 8;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    printf("Belosludceva Vlada Dmitrievna\nGroup: I914B\n");

    printf("Client started (Priority: %d, Policy: RR)\n", param.sched_priority);
    printf("Enter server PID: ");
    scanf("%ld", &serv_pid);
    printf("Connecting to server PID: %ld\n", serv_pid);

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    if(coid == -1) {
        perror("ConnectAttach failed");
        return 1;
    }

    printf("Enter message to send: ");
    scanf("%255s", smsg);
    printf("Sending message: \"%s\"\n", smsg);

    if(MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
        perror("MsgSend failed");
    } else {
        printf("Received reply: \"%s\"\n", rmsg);
    }

    ConnectDetach(coid);
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/sched.h>

void server(void) {
    int rcvid;
    int chid;
    char message[200];
    struct sched_param param;

    // Устанавливаем приоритет и алгоритм планирования (FIFO)
    param.sched_priority = 7;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    printf("Belosludceva Vlada Dmitrievna\nGroup: I914B\n");

    printf("Server start working (Priority: %d, Policy: FIFO)\n", param.sched_priority);

    chid = ChannelCreate(0);
    printf("Channel id: %d \n", chid);
    printf("Server PID: %d \n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        printf("Received message, rcvid %X \n", rcvid);
        printf("Message content: \"%s\"\n", message);
        
        strcpy(message, "Server response (FIFO priority 7)");
        MsgReply(rcvid, EOK, message, sizeof(message));
        printf("Sent reply: \"%s\"\n", message);
    }
}

int main(void) {
    printf("Starting server...\n");
    server();
    return 0;
}

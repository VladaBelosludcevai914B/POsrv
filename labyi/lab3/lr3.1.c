#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

void invert_case(const char* input, char* output) {
    int i = 0;
    while (input[i]) {
        if (islower(input[i])) {
            output[i] = toupper(input[i]);
        } else if (isupper(input[i])) {
            output[i] = tolower(input[i]);
        } else {
            output[i] = input[i]; // оставляем без изменений если не буква
        }
        i++;
    }
    output[i] = '\0';
}

void server(void) {
    int rcvid;
    int chid;
    char received[512];
    char inverted[512];

    printf("Case inversion server started\n");

    if ((chid = ChannelCreate(0)) == -1) {
        perror("ChannelCreate");
        exit(EXIT_FAILURE);
    }

    printf("Channel id: %d\n", chid);
    printf("Server PID: %d\n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, received, sizeof(received), NULL);
        if (rcvid == -1) {
            perror("MsgReceive");
            continue;
        }

        printf("Received string: \"%s\"\n", received);

        invert_case(received, inverted);
        printf("Inverted case: \"%s\"\n", inverted);

        if (MsgReply(rcvid, 0, inverted, strlen(inverted) + 1) == -1) {
            perror("MsgReply");
        }
    }
}

int main(void) {
    printf("Case inversion server program\n");
    server();
    printf("Belosludceva Vlada Dmitrievna\nGroup: I914B\n");
    return EXIT_SUCCESS;
}

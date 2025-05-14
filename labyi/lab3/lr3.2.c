#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <errno.h>
#include <ctype.h>

int main(void) {
    char original[512];
    char inverted[512];
    int coid;
    long serv_pid;

    printf("Case inversion client. Enter server PID: ");
    scanf("%ld", &serv_pid);
    printf("Connecting to server PID: %ld\n", serv_pid);

    if ((coid = ConnectAttach(0, serv_pid, 1, 0, 0)) == -1) {
        perror("ConnectAttach");
        exit(EXIT_FAILURE);
    }

    printf("Enter string to invert case: ");
    scanf("%511s", original);
    printf("Sending string: \"%s\"\n", original);

    if (MsgSend(coid, original, strlen(original) + 1, inverted, sizeof(inverted)) == -1) {
        perror("MsgSend");
        ConnectDetach(coid);
        exit(EXIT_FAILURE);
    }

    printf("Server response (inverted case): \"%s\"\n", inverted);
    printf("Belosludceva Vlada Dmitrievna\nGroup: I914B\n");
    ConnectDetach(coid);
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 1024


void split_by_char(char* buffer, pid_t pid) {
    char token;
    while(*buffer) {
        token = *buffer;
        ++buffer;
        int j = 0;
        while(j < 8) {
            if(token & 1) {
                kill(pid, SIGUSR1);
            }else {
                kill(pid, SIGUSR2);
            }
            usleep(500);
            token = token >> 1;
            ++j;
        }
    }
    
}


int main (int argc, char **argv) {
    printf("You can communicate with the server by typing text\n");
    pid_t pid = atoi(argv[1]);
    char buffer[DEFAULT_BUFFER_SIZE];

    while(1) {
        scanf("%[^\n]", buffer);
        fflush(stdin);
        split_by_char(buffer, pid);
    }
}

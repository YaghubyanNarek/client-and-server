#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define DEFAULT_BUFFER_SIZE 1024

char symbol;

void rec(int bit) {
    static int bitCount = 0;
    symbol |= (bit << bitCount);
    bitCount++;
    if (bitCount == 8) {
        printf("%c", symbol);
        fflush(stdout);
        bitCount = 0;
        symbol = 0;
    }
}

void signal_handler1(int signal){
    rec(0);
}

void signal_handler (int signal) {
    rec(1);
}

int main () {
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler1);
    pid_t pid = getpid();
    printf("My pid is %d\n", pid);
    while(1);
    return 0;
}

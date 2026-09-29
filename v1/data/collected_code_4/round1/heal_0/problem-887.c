#include <stdio.h>
#include <stdlib.h>

int isOdd(int num) {
    return num & 1;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s number\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    if (isOdd(num)) {
        printf("%d is odd.\n", num);
    } else {
        printf("%d is not odd.\n", num);
    }

    return 0;
}
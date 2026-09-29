#include <stdio.h>
#include <string.h>

#define ASCII_SIZE 256 

void countCharFreq(char* str, int* freq) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        freq[(int)str[i]]++;
    }
}

int main() {
    char str[] = "Hello, World!";
    int freq[ASCII_SIZE] = {0};

    countCharFreq(str, freq);

    int i;
    for (i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] != 0) {
            printf("'%c' has frequency %d\n", i, freq[i]);
        }
    }

    return 0;
}
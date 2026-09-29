#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countCharacterFrequency(const char *input, int *frequency) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] >= 0 && input[i] <= 255) {
            frequency[(unsigned char)input[i]]++;
        }
    }
}

int main() {
    const char *input = "Hello, World!";
    int frequency[256] = {0};

    countCharacterFrequency(input, frequency);

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            printf("%c: %d\n", i, frequency[i]);
        }
    }

    return 0;
}
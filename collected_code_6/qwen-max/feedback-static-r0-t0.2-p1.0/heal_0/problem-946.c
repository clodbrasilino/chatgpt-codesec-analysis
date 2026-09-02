#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 256

void findMostCommonElements(const char *text, int *mostCommon, int *counts) {
    int frequency[MAX_CHAR] = {0};
    int maxCount = 0;

    while (*text) {
        if (isalpha(*text)) {
            int index = tolower(*text);
            frequency[index]++;
            if (frequency[index] > maxCount) {
                maxCount = frequency[index];
            }
        }
        text++;
    }

    int count = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (frequency[i] == maxCount && isalpha(i)) {
            mostCommon[count] = i;
            counts[count] = maxCount;
            count++;
        }
    }
}

int main() {
    const char *text = "Example text with some letters and symbols!";
    int mostCommon[10];
    int counts[10];

    findMostCommonElements(text, mostCommon, counts);

    for (int i = 0; i < 10; i++) {
        if (mostCommon[i] != 0) {
            printf("Character: %c, Count: %d\n", mostCommon[i], counts[i]);
        } else {
            break;
        }
    }

    return 0;
}
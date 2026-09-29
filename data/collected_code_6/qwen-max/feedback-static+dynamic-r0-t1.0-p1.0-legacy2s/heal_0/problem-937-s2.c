#include <stdio.h>
#include <string.h>
#include <limits.h>

int count_most_common_char(const char *str, char *most_common, int *max_count) {
    if (str == NULL || most_common == NULL || max_count == NULL) {
        return -1;
    }

    int counts[256] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
    }

    *max_count = 0;
    *most_common = '\0';
    for (int i = 0; i < 256; i++) {
        if (counts[i] > *max_count) {
            *max_count = counts[i];
            *most_common = (char)i;
        }
    }

    return 0;
}

int main() {
    const char *input = "hello world";
    char most_common;
    int max_count;

    if (count_most_common_char(input, &most_common, &max_count) == 0) {
        printf("Most common character: '%c' with %d occurrences\n", most_common, max_count);
    } else {
        printf("Error in counting most common character.\n");
    }

    return 0;
}
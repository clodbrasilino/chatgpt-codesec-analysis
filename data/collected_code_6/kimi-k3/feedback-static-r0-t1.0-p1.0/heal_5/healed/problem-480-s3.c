#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

char findMaxOccurringChar(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    size_t count[UCHAR_MAX + 1] = {0};
    size_t len = strnlen(str, max_len);

    if (len == 0) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    size_t maxCount = 0;
    char maxChar = '\0';

    for (int j = 0; j <= UCHAR_MAX; j++) {
        if (count[j] > maxCount) {
            maxCount = count[j];
            maxChar = (char)j;
        }
    }

    return maxChar;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t len;

    printf("Enter a string: ");
    
    len = getline(&str, &size, stdin);
    
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("Empty string provided\n");
        free(str);
        return 1;
    }

    char maxChar = findMaxOccurringChar(str, (size_t)len);

    if (maxChar != '\0') {
        printf("Maximum occurring character: '%c'\n", maxChar);
    } else {
        printf("No characters found\n");
    }

    free(str);
    return 0;
}
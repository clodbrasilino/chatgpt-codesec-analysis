#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str, size_t size) {
    if (!str || size <= 0) {
        return;
    }

    size_t i = 0, j = 0;
    while (str[i] != '\0' && i < size) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
        i++;
    }

    if (j < size) {
        str[j] = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, MAX_SIZE);

        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (len >= MAX_SIZE - 1) {
            printf("Input string is too long. Maximum supported length is %d.\n", MAX_SIZE - 1);
            return 0;
        }

        if (str[0] != '\0') {
            removeNonAlphanumeric(str, MAX_SIZE);
            printf("String after removing non-alphanumeric characters: %s\n", str);
        }
    }
    return 0;
}
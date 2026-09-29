#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void removeChars(char *str1, const char *str2) {
    if(!str1 || !str2 || strnlen(str1, BUFFER_SIZE) >= BUFFER_SIZE || strnlen(str2, BUFFER_SIZE) >= BUFFER_SIZE) {
        return;
    }

    size_t count = 0;

    for (size_t i = 0; i < strnlen(str1, BUFFER_SIZE); i++) {
        bool found = false;

        for (size_t j = 0; j < strnlen(str2, BUFFER_SIZE); j++) {
            if(str1[i] == str2[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            str1[count] = str1[i];
            count++;
        }
    }

    str1[count] = '\0';
}

int main() {
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];

    printf("Enter the first string: ");
    if (fgets(str1, BUFFER_SIZE, stdin)) {
        str1[strcspn(str1, "\n")] = '\0';

        printf("Enter the second string: ");
        if (fgets(str2, BUFFER_SIZE, stdin)) {
            str2[strcspn(str2, "\n")] = '\0';

            removeChars(str1, str2);
            printf("Modified string: %s\n", str1);
        } else {
            printf("An error occurred while reading the second string\n");
        }
    } else {
        printf("An error occurred while reading the first string\n");
    }

    return 0;
}
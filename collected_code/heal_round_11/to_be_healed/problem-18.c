#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void removeChars(char *str1, const char *str2) {
    if(!str1 || !str2) {
        return;
    }

    size_t str2_len = strnlen(str2, BUFFER_SIZE);
    size_t str1_len = strnlen(str1, BUFFER_SIZE);
    size_t count = 0;

    for (size_t i = 0; i < str1_len && i < BUFFER_SIZE; i++) {
        bool found = false;

        for (size_t j = 0; j < str2_len && j < BUFFER_SIZE; j++) {
            if(str1[i] == str2[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            str1[count] = str1[i];
            if(count < BUFFER_SIZE - 1) {
                count++;
            }
        }
    }

    if(count < BUFFER_SIZE) {
        str1[count] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];

    printf("Enter the first string: ");
    if (fgets(str1, BUFFER_SIZE, stdin)) {
        str1[strcspn(str1, "\n")] = 0;

        printf("Enter the second string: ");
        if (fgets(str2, BUFFER_SIZE, stdin)) {
            str2[strcspn(str2, "\n")] = 0;

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
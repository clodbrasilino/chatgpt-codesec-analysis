#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#define MAX_INPUT_LENGTH (1024u * 1024u)

int first_repeated_character(const char *str) {
    size_t char_count[UCHAR_MAX + 1] = {0};
    const unsigned char *ptr;
    size_t i = 0;

    if (str == NULL) {
        return -1;
    }

    ptr = (const unsigned char *)str;

    while (ptr[i] != '\0') {
        char_count[ptr[i]]++;
        i++;
    }

    i = 0;
    while (ptr[i] != '\0') {
        if (char_count[ptr[i]] > 1) {
            return ptr[i];
        }
        i++;
    }

    return -1;
}

char *read_input(void) {
    size_t capacity = 128;
    size_t len = 0;
    char *buffer = malloc(capacity);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[4096];
    int done = 0;

    if (!buffer) {
        return NULL;
    }

    while (!done && fgets(temp, sizeof(temp), stdin)) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t temp_len = strlen(temp);

        if (temp_len > 0 && temp[temp_len - 1] == '\n') {
            done = 1;
            temp_len--;
        }

        if (len + temp_len + 1 > capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity < capacity) {
                free(buffer);
                return NULL;
            }

            if (new_capacity > MAX_INPUT_LENGTH + 1) {
                new_capacity = MAX_INPUT_LENGTH + 1;
            }

            if (len + temp_len + 1 > new_capacity) {
                if (len + temp_len + 1 > MAX_INPUT_LENGTH + 1) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = len + temp_len + 1;
            }

            char *newbuf = realloc(buffer, new_capacity);
            if (!newbuf) {
                free(buffer);
                return NULL;
            }

            buffer = newbuf;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + len, temp, temp_len);
        len += temp_len;
    }

    if (len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int main(void) {
    char *input = read_input();
    int result;

    if (input == NULL) {
        return 1;
    }

    result = first_repeated_character(input);

    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    free(input);
    return 0;
}
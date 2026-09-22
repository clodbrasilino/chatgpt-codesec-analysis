#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

char *read_line_dynamic(void) {
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char chunk[128];

    while (fgets(chunk, sizeof(chunk), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t chunk_len = strlen(chunk);
        int eol = (chunk_len > 0 && chunk[chunk_len - 1] == '\n');

        if (eol) {
            chunk_len--;
        }

        if (length + chunk_len + 1 > capacity) {
            size_t new_capacity = capacity;
            while (new_capacity < length + chunk_len + 1) {
                if (new_capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity *= 2;
            }
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + length, chunk, chunk_len);
        length += chunk_len;

        if (eol) {
            break;
        }
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void) {
    char *input = read_line_dynamic();
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
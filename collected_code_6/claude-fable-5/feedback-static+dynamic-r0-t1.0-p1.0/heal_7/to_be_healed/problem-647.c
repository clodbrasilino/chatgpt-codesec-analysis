#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

char **split_at_uppercase(const char *input, size_t *count);
void free_split(char **parts, size_t count);

char **split_at_uppercase(const char *input, size_t *count)
{
    size_t len;
    size_t capacity = 8;
    size_t num = 0;
    size_t start = 0;
    size_t i;
    char **result;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        if (i == len || (i > 0 && isupper((unsigned char)input[i]))) {
            size_t seglen = i - start;
            char *segment;

            if (seglen == 0) {
                start = i;
                continue;
            }

            if (start > len || seglen > len - start || seglen >= SIZE_MAX) {
                for (size_t j = 0; j < num; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            segment = malloc(seglen + 1);
            if (segment == NULL) {
                for (size_t j = 0; j < num; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(segment, input + start, seglen);
            segment[seglen] = '\0';

            if (num >= capacity) {
                size_t new_capacity;
                char **tmp;

                if (capacity > SIZE_MAX / 2 ||
                    (capacity * 2) > SIZE_MAX / sizeof(char *)) {
                    free(segment);
                    for (size_t j = 0; j < num; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                new_capacity = capacity * 2;
                tmp = realloc(result, new_capacity * sizeof(char *));
                if (tmp == NULL) {
                    free(segment);
                    for (size_t j = 0; j < num; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                result = tmp;
                capacity = new_capacity;
            }

            result[num] = segment;
            num++;
            start = i;
        }
    }

    *count = num;
    return result;
}

void free_split(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int main(void)
{
    const char *text = "helloWorldThisIsATest";
    size_t count = 0;
    size_t i;
    char **parts;

    parts = split_at_uppercase(text, &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", parts[i]) < 0) {
            free_split(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);
    return EXIT_SUCCESS;
}
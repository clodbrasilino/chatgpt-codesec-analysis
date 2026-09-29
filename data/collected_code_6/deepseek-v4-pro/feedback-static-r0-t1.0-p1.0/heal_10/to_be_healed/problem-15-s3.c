#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* str, int* count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    size_t capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int segment_count = 0;
    size_t segment_start = 0;
    size_t i;

    for (i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t segment_len = i - segment_start;
            if (segment_len > 0) {
                if ((size_t)segment_count >= capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity <= capacity) {
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char** temp = realloc(result, new_capacity * sizeof(char*));
                    if (temp == NULL) {
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                result[segment_count] = malloc(segment_len + 1);
                if (result[segment_count] == NULL) {
                    for (int j = 0; j < segment_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[segment_count], str + segment_start, segment_len);
                result[segment_count][segment_len] = '\0';
                segment_count++;
            }
            segment_start = i + 1;
        }
    }

    if (segment_count == 0) {
        free(result);
        *count = 0;
        return NULL;
    }

    *count = segment_count;
    return result;
}

int main(void) {
    const char* test_string = "HelloWorldThisIsATest";
    int count = 0;
    char** parts = split_at_lowercase(test_string, &count);

    if (parts == NULL) {
        printf("No parts found or error occurred\n");
        return 0;
    }

    printf("Split results:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 1000000
#define INITIAL_CAPACITY 10

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < MAX_STRING_LENGTH && str[len] != '\0') {
        len++;
    }
    if (len >= MAX_STRING_LENGTH && str[len] != '\0') {
        return NULL;
    }

    size_t capacity = INITIAL_CAPACITY;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t segment_start = 0;
    int segment_count = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t segment_len = i - segment_start;
            if (segment_len > 0) {
                if ((size_t)segment_count >= capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) {
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **temp = realloc(result, new_capacity * sizeof(char *));
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
    const char *test_str = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_lowercase(test_str, &count);

    if (parts != NULL) {
        printf("Split into %d parts:\n", count);
        for (int i = 0; i < count; i++) {
            printf("[%d]: %s\n", i, parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("No lowercase letters found or error occurred.\n");
    }

    const char *test_str2 = "ALLUPPERCASE";
    count = 0;
    parts = split_at_lowercase(test_str2, &count);

    if (parts != NULL) {
        printf("Split into %d parts:\n", count);
        for (int i = 0; i < count; i++) {
            printf("[%d]: %s\n", i, parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("No lowercase letters found or error occurred.\n");
    }

    const char *test_str3 = "abcDefGhi";
    count = 0;
    parts = split_at_lowercase(test_str3, &count);

    if (parts != NULL) {
        printf("Split into %d parts:\n", count);
        for (int i = 0; i < count; i++) {
            printf("[%d]: %s\n", i, parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("No lowercase letters found or error occurred.\n");
    }

    return 0;
}
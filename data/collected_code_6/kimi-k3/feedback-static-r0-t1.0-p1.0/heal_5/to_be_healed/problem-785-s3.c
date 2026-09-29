#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntTuple;

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int parse_tuple_string(const char *str, size_t str_len, IntTuple *result) {
    char *buffer = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    int *temp_array = NULL;
    size_t count = 0;
    size_t capacity = 10;
    size_t start = 0;
    size_t end = 0;
    size_t len = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    result->data = NULL;
    result->size = 0;

    while (start < str_len && isspace((unsigned char)str[start])) {
        start++;
    }

    if (start >= str_len || str[start] != '(') {
        return -1;
    }
    start++;

    end = str_len;
    while (end > start && isspace((unsigned char)str[end - 1])) {
        end--;
    }

    if (end <= start || str[end - 1] != ')') {
        return -1;
    }
    end--;

    len = end - start;
    if (len == 0) {
        return 0;
    }

    if (len > SIZE_MAX - 1) {
        return -1;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Comparison is wrong. Result of 'str+start' can't be 0 unless there is pointer overflow, and pointer overflow is undefined behaviour. [pointerAdditionResultNotNull]
     */
    if (len > 0 && str + start != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, str + start, len);
    }
    buffer[len] = '\0';

    temp_array = malloc(capacity * sizeof(int));
    if (temp_array == NULL) {
        free(buffer);
        return -1;
    }

    token = strtok_r(buffer, ",", &saveptr);
    while (token != NULL) {
        char *endptr = NULL;
        long val = 0;

        while (isspace((unsigned char)*token)) {
            token++;
        }

        if (*token == '\0') {
            free(temp_array);
            free(buffer);
            return -1;
        }

        errno = 0;
        val = strtol(token, &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            free(temp_array);
            free(buffer);
            return -1;
        }

        if (endptr == token) {
            free(temp_array);
            free(buffer);
            return -1;
        }

        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (*endptr != '\0') {
            free(temp_array);
            free(buffer);
            return -1;
        }

        if (count >= capacity) {
            size_t new_capacity;
            int *new_array;
            
            if (capacity > SIZE_MAX / 2) {
                free(temp_array);
                free(buffer);
                return -1;
            }
            
            new_capacity = capacity * 2;
            
            if (new_capacity > SIZE_MAX / sizeof(int)) {
                free(temp_array);
                free(buffer);
                return -1;
            }
            
            new_array = realloc(temp_array, new_capacity * sizeof(int));
            if (new_array == NULL) {
                free(temp_array);
                free(buffer);
                return -1;
            }
            temp_array = new_array;
            capacity = new_capacity;
        }

        temp_array[count] = (int)val;
        count++;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(buffer);

    if (count == 0) {
        free(temp_array);
        return 0;
    }

    result->data = temp_array;
    result->size = count;
    return 0;
}

int main(void) {
    const char test_str[] = "(10, 20, 30, -5, 42)";
    IntTuple tuple = {0};

    if (parse_tuple_string(test_str, sizeof(test_str) - 1, &tuple) == 0) {
        printf("Parsed %zu elements:\n", tuple.size);
        for (size_t i = 0; i < tuple.size; i++) {
            printf("%d ", tuple.data[i]);
        }
        printf("\n");
        free_tuple(&tuple);
    } else {
        fprintf(stderr, "Failed to parse tuple string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
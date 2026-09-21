#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    int *positions;
} SubstringResult;

SubstringResult *find_substrings(const char *str, const char *sub) {
    SubstringResult *result = NULL;
    size_t str_len;
    size_t sub_len;
    size_t capacity;
    size_t i;

    if (str == NULL || sub == NULL) {
        return NULL;
    }

    str_len = strnlen(str, SIZE_MAX);
    sub_len = strnlen(sub, SIZE_MAX);

    if (sub_len == 0 || sub_len > str_len) {
        result = (SubstringResult *)malloc(sizeof(SubstringResult));
        if (result == NULL) {
            return NULL;
        }
        result->count = 0;
        result->positions = NULL;
        return result;
    }

    result = (SubstringResult *)malloc(sizeof(SubstringResult));
    if (result == NULL) {
        return NULL;
    }

    capacity = 10;
    result->positions = (int *)malloc(capacity * sizeof(int));
    if (result->positions == NULL) {
        free(result);
        return NULL;
    }

    result->count = 0;

    for (i = 0; i <= str_len - sub_len; i++) {
        if (strncmp(str + i, sub, sub_len) == 0) {
            if ((size_t)result->count >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result->positions, capacity * sizeof(int));
                if (temp == NULL) {
                    free(result->positions);
                    free(result);
                    return NULL;
                }
                result->positions = temp;
            }
            result->positions[result->count] = (int)i;
            result->count++;
            i += sub_len - 1;
        }
    }

    if (result->count == 0) {
        free(result->positions);
        result->positions = NULL;
    }

    return result;
}

void free_substring_result(SubstringResult *result) {
    if (result != NULL) {
        if (result->positions != NULL) {
            free(result->positions);
        }
        free(result);
    }
}

int main(void) {
    const char *text = "this is a test string for testing the test function";
    const char *pattern = "test";
    
    SubstringResult *res = find_substrings(text, pattern);
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    printf("Substring '%s' found %d times.\n", pattern, res->count);
    printf("Positions: ");
    for (int i = 0; i < res->count; i++) {
        printf("%d ", res->positions[i]);
    }
    printf("\n");

    free_substring_result(res);

    return EXIT_SUCCESS;
}
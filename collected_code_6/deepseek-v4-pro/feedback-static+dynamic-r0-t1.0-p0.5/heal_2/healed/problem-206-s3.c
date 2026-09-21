#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_adjacent(const char* tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(tuple[i], SIZE_MAX);
        total_length += len;
        if (total_length < len) {
            return NULL;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* current = result;
    for (int i = 0; i < size; i++) {
        size_t len = strnlen(tuple[i], total_length - (current - result));
        if (len > total_length - (current - result)) {
            free(result);
            return NULL;
        }
        memcpy(current, tuple[i], len);
        current += len;
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* tuple1[] = {"Hello", " ", "World", "!"};
    char* result1 = concatenate_adjacent(tuple1, 4);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char* tuple2[] = {"abc", "def", "ghi"};
    char* result2 = concatenate_adjacent(tuple2, 3);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char* tuple3[] = {"single"};
    char* result3 = concatenate_adjacent(tuple3, 1);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    printf("NULL input handled\n");

    return 0;
}
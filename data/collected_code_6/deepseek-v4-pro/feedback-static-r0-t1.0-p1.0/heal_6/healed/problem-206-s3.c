#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concat_adjacent_elements(const char *tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = (size_t *)malloc((size_t)size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        
        const char *str = tuple[i];
        size_t len = 0;
        while (str[len] != '\0') {
            len++;
            if (len > SIZE_MAX - total_length) {
                free(lengths);
                return NULL;
            }
        }
        
        lengths[i] = len;
        if (total_length > SIZE_MAX - len) {
            free(lengths);
            return NULL;
        }
        total_length += len;
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t pos = 0;
    for (int i = 0; i < size; i++) {
        size_t dest_remaining = total_length - pos;
        if (lengths[i] > dest_remaining) {
            free(result);
            free(lengths);
            return NULL;
        }
        
        for (size_t j = 0; j < lengths[i]; j++) {
            result[pos + j] = tuple[i][j];
        }
        pos += lengths[i];
    }
    result[pos] = '\0';

    free(lengths);
    return result;
}

int main(void) {
    const char *tuple1[] = {"hello", "world", "123"};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    
    char *result1 = concat_adjacent_elements(tuple1, size1);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char *tuple2[] = {"a", "b", "c", "d"};
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    
    char *result2 = concat_adjacent_elements(tuple2, size2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char *tuple3[] = {"single"};
    int size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    
    char *result3 = concat_adjacent_elements(tuple3, size3);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    return 0;
}
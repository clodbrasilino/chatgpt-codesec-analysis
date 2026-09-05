#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_concat(const char** tuples, int count) {
    if (tuples == NULL || count < 2) {
        return NULL;
    }

    int result_count = count - 1;
    char** result = (char**)malloc(result_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < result_count; i++) {
        size_t len1 = strlen(tuples[i]);
        size_t len2 = strlen(tuples[i + 1]);
        
        result[i] = (char*)malloc(len1 + len2 + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        memcpy(result[i], tuples[i], len1);
        memcpy(result[i] + len1, tuples[i + 1], len2);
        result[i][len1 + len2] = '\0';
    }

    return result;
}

void free_concat_result(char** result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* tuples[] = {"Hello", "World", "C", "Programming"};
    int count = sizeof(tuples) / sizeof(tuples[0]);

    if (count < 2) {
        return 1;
    }

    char** result = adjacent_concat(tuples, count);
    if (result == NULL) {
        return 1;
    }

    int result_count = count - 1;
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    free_concat_result(result, result_count);

    return 0;
}
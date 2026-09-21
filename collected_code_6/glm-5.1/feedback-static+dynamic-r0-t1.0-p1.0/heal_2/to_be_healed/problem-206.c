#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent_tuples(char** tuples, const int* sizes, int count, int* result_count) {
    *result_count = count - 1;
    if (count < 2) {
        return NULL;
    }

    char** result = (char**)malloc(*result_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < *result_count; i++) {
        int len1 = sizes[i];
        int len2 = sizes[i + 1];
        size_t total_len = (size_t)len1 + (size_t)len2;

        result[i] = (char*)malloc((total_len + 1) * sizeof(char));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  did you mean 'memcpy'?
         */
        errno_t err1 = memcpy_s(result[i], total_len + 1, tuples[i], len1);
        if (err1 != 0) {
            free(result[i]);
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        errno_t err2 = memcpy_s(result[i] + len1, total_len - len1 + 1, tuples[i + 1], len2);
        if (err2 != 0) {
            free(result[i]);
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[i][total_len] = '\0';
    }

    return result;
}

int main() {
    char* tuples[] = {"abc", "def", "gh", "ijk"};
    int sizes[] = {3, 3, 2, 3};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    int result_count = 0;

    char** result = concatenate_adjacent_tuples(tuples, sizes, count, &result_count);

    if (result != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
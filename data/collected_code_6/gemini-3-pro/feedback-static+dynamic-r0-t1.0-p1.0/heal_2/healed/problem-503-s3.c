#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    if (length == 0) {
        *out_length = 0;
        return NULL;
    }

    if (length == 1) {
        *out_length = 1;
        int* result = (int*)malloc(sizeof(int));
        if (result != NULL) {
            result[0] = list[0];
        }
        return result;
    }

    *out_length = length - 1;
    int* result = (int*)malloc(*out_length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_length; ++i) {
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[10000];
    size_t length = 0;
    int c;

    while (length < 10000) {
        c = getchar();
        if (c == EOF) {
            break;
        }
        if (isdigit((unsigned char)c) || c == '-') {
            ungetc(c, stdin);
            if (scanf("%d", &list[length]) == 1) {
                length++;
            } else {
                getchar();
            }
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    if (result != NULL || length > 0) {
        for (size_t i = 0; i < out_length; ++i) {
            printf("%d", result[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        free(result);
    }
    printf("]\n");

    return 0;
}
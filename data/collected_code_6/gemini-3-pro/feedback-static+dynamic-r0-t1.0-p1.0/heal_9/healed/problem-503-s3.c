#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    if (length <= 1) {
        *out_length = 0;
        return NULL;
    }

    *out_length = length - 1;
    int* result = (int*)malloc(*out_length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_length; ++i) {
        long long sum = (long long)list[i] + list[i + 1];
        if (sum > INT_MAX) {
            result[i] = INT_MAX;
        } else if (sum < INT_MIN) {
            result[i] = INT_MIN;
        } else {
            result[i] = (int)sum;
        }
    }

    return result;
}

int main(void) {
    int list[10000];
    size_t length = 0;
    int num;
    int c;

    while (length < 10000) {
        if (scanf("%d", &num) == 1) {
            list[length++] = num;
        } else {
            c = getchar();
            if (c == EOF) {
                break;
            }
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    if (result != NULL) {
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
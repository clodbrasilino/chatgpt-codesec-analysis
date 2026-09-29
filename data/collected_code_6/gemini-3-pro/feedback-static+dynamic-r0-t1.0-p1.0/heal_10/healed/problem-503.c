#include <stdio.h>
#include <stdlib.h>

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        if (out_length) *out_length = 0;
        return NULL;
    }

    if (length <= 1) {
        *out_length = 0;
        return NULL;
    }

    *out_length = length - 1;
    int* result = (int*)malloc((*out_length) * sizeof(int));
    if (result == NULL) {
        *out_length = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_length; i++) {
        result[i] = (int)((unsigned int)list[i] + (unsigned int)list[i + 1]);
    }

    return result;
}

int main(void) {
    size_t capacity = 16;
    size_t length = 0;
    int* list = (int*)malloc(capacity * sizeof(int));
    
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    int ch;
    long long num = 0;
    int sign = 1;
    int in_num = 0;

    while ((ch = getchar()) != EOF) {
        if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
            in_num = 1;
        } else if (ch == '-' && !in_num) {
            sign = -1;
        } else {
            if (in_num) {
                if (length == capacity) {
                    capacity *= 2;
                    int* temp = (int*)realloc(list, capacity * sizeof(int));
                    if (temp == NULL) {
                        free(list);
                        return EXIT_FAILURE;
                    }
                    list = temp;
                }
                list[length++] = (int)(num * sign);
                num = 0;
                sign = 1;
                in_num = 0;
            } else if (ch != '-') {
                sign = 1; 
            }
        }
    }
    if (in_num) {
        if (length == capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(list, capacity * sizeof(int));
            if (temp != NULL) {
                list = temp;
            }
        }
        if (list != NULL) {
            list[length++] = (int)(num * sign);
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    if (result != NULL && out_length > 0) {
        printf("[");
        for (size_t i = 0; i < out_length; i++) {
            printf("%d", result[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    } else {
        printf("[]\n");
    }

    free(list);
    return EXIT_SUCCESS;
}
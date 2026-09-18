#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[10000];
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch == '[') {
            length = 0;
            int num;
            int last_char = ch;
            
            while (scanf("%d", &num) == 1) {
                if (length < 10000) {
                    list[length++] = num;
                }
                while ((last_char = getchar()) != EOF && last_char != ',' && last_char != ']') {
                }
                if (last_char == ']') {
                    break;
                }
            }
            
            while (last_char != ']' && last_char != EOF) {
                last_char = getchar();
            }
            
            size_t out_length = 0;
            int* result = add_consecutive_numbers(list, length, &out_length);
            
            printf("[");
            if (result != NULL && out_length > 0) {
                for (size_t i = 0; i < out_length; ++i) {
                    printf("%d", result[i]);
                    if (i < out_length - 1) {
                        printf(", ");
                    }
                }
                free(result);
            }
            printf("]\n");
        }
    }

    return 0;
}
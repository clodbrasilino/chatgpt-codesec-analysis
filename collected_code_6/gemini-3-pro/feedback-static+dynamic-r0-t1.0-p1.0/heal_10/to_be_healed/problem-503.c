#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        if (out_length) *out_length = 0;
        return NULL;
    }

    if (length == 0) {
        *out_length = 0;
        return NULL;
    }

    if (length == 1) {
        int* result = (int*)malloc(sizeof(int));
        if (result == NULL) {
            *out_length = 0;
            return NULL;
        }
        result[0] = list[0];
        *out_length = 1;
        return result;
    }

    *out_length = length - 1;
    int* result = (int*)malloc((*out_length) * sizeof(int));
    if (result == NULL) {
        *out_length = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_length; i++) {
        result[i] = list[i] + list[i + 1];
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
    while ((ch = getchar()) != EOF) {
        if (ch == ']') {
            break;
        }
        if ((ch >= '0' && ch <= '9') || ch == '-') {
            ungetc(ch, stdin);
            int num;
            if (scanf("%d", &num) == 1) {
                if (length == capacity) {
                    capacity *= 2;
                    int* temp = (int*)realloc(list, capacity * sizeof(int));
                    if (temp == NULL) {
                        free(list);
                        return EXIT_FAILURE;
                    }
                    list = temp;
                }
                list[length++] = num;
            }
        }
    }

    if (length == 0) {
        printf("[]\n");
        free(list);
        return EXIT_SUCCESS;
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    for (size_t i = 0; i < out_length; i++) {
        printf("%d", result[i]);
        if (i < out_length - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    if (result != NULL) {
        free(result);
    } 

    free(list);
    return EXIT_SUCCESS;
}
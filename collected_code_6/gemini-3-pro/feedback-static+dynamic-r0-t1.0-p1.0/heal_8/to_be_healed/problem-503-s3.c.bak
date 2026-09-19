#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

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
    int has_bracket = 0;

    while (1) {
        int val;
        int res = scanf("%d", &val);
        if (res == 1) {
            if (length < 10000) {
                list[length++] = val;
            }
        } else {
            int c = getchar();
            if (c == EOF) {
                break;
            } else if (c == '[') {
                has_bracket = 1;
                length = 0;
            } else if (c == ']' || c == '\n') {
                if (has_bracket || length > 0) {
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
                    
                    length = 0;
                    has_bracket = 0;
                }
            }
        }
    }

    return 0;
}
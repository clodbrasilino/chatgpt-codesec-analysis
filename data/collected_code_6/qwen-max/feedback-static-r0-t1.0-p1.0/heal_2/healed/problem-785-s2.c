#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* stringToIntegerTuple(const char *str, int *len) {
    int i = 0, j = 0, k = 0;
    int num = 0;
    int *tuple = NULL;

    if (str == NULL || len == NULL)
        return NULL;

    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '(')
            continue;
        if (str[i] == ',') {
            if (k > 0) {
                tuple = realloc(tuple, (j + 1) * sizeof(int));
                if (tuple == NULL) {
                    free(tuple);
                    return NULL;
                }
                tuple[j++] = num;
                num = 0;
                k = 0;
            }
        } else if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
            k++;
        }
    }
    if (k > 0) {
        tuple = realloc(tuple, (j + 1) * sizeof(int));
        if (tuple == NULL) {
            free(tuple);
            return NULL;
        }
        tuple[j++] = num;
    }

    *len = j;
    return tuple;
}

int main() {
    const char *input = "(123,456,789)";
    int len = 0;
    int *result = stringToIntegerTuple(input, &len);

    if (result != NULL) {
        for (int i = 0; i < len; i++) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    return 0;
}
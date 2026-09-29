#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as const array [constParameter]
 */
char *concat_adjacent_elements(char *const tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    int total_length = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strlen(tuple[i]);
    }

    char *result = (char *)malloc((total_length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int pos = 0;
    for (int i = 0; i < size; i++) {
        strcpy(result + pos, tuple[i]);
        pos += strlen(tuple[i]);
    }
    result[pos] = '\0';

    return result;
}

int main(void) {
    const char *tuple1[] = {"hello", "world", "123"};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);

    char *result1 = concat_adjacent_elements((char *const *)tuple1, size1);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char *tuple2[] = {"a", "b", "c", "d"};
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    char *result2 = concat_adjacent_elements((char *const *)tuple2, size2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char *tuple3[] = {"single"};
    int size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    char *result3 = concat_adjacent_elements((char *const *)tuple3, size3);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    return 0;
}
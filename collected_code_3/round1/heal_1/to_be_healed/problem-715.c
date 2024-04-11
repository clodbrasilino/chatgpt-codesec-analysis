#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple string_to_tuple(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == ',') {
            count++;
        }
    }

    Tuple tuple;
    tuple.size = count + 1;
    tuple.data = (int *)malloc(tuple.size * sizeof(int));

    char *token = strtok(str, ",");
    for (int i = 0; token != NULL; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple.data[i] = atoi(token);
        token = strtok(NULL, ",");
    }

    return tuple;
}

int main() {
    char str[] = "1,2,3,4,5";
    Tuple tuple = string_to_tuple(str);

    printf("(");
    for (int i = 0; i < tuple.size; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*_1 + _3' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        printf("%d", tuple.data[i]);
        if (i < tuple.size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(tuple.data);

    return 0;
}
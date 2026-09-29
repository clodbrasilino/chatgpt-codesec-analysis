#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple string_to_tuple(char *str) {
    Tuple tuple = {NULL, 0};
    char *token;
    int count = 0;

    token = strtok(str, ",");
    while (token != NULL) {
        /* Possible weaknesses found:
         *  leak of 'tuple.data' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        tuple.data = realloc(tuple.data, (count + 1) * sizeof(int));
        
        if(tuple.data == NULL) return tuple;
        
        tuple.data[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    tuple.size = count;

    return tuple;
}

int main() {
    char str[] = "1,2,3,4,5";
    Tuple tuple;
    int i;

    tuple = string_to_tuple(str);

    if(tuple.data == NULL) return 1;

    printf("(");
    for (i = 0; i < tuple.size; i++) {
        printf("%d", tuple.data[i]);
        if (i < tuple.size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(tuple.data);

    return 0;
}
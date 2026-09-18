#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple str_to_tuple(char *str) {
    Tuple tuple;
    char *token = strtok(str, " ");

    if (token != NULL) {
        tuple.first = atoi(token);
        token = strtok(NULL, " ");

        if (token != NULL) {
            tuple.second = atoi(token);
        } else {
            printf("Error: Not enough integers in the string.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Error: Not enough integers in the string.\n");
        exit(EXIT_FAILURE);
    }
    return tuple;
}

int main() {
    char str[] = "9 27";
    Tuple tuple = str_to_tuple(str);

    printf("First value: %d, Second value: %d\n", tuple.first, tuple.second);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_tuple_string_to_int(char *tuple_str, int *tuple_int) {
    char *token = strtok(tuple_str, ",");
    int i = 0;
    while (token != NULL) {
        tuple_int[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
}

int main() {
    char tuple_str[100];
    int tuple_int[100];
    printf("Enter the tuple string: ");
    fgets(tuple_str, 100, stdin);
    tuple_str[strcspn(tuple_str, "\n")] = 0;
    convert_tuple_string_to_int(tuple_str, tuple_int);
    for (int i = 0; i < 100 && tuple_int[i] != 0; i++) {
        printf("%d ", tuple_int[i]);
    }
    return 0;
}
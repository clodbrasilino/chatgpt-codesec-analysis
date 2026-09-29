#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100

void convert_string_to_tuple(char *str, int *arr, int *size) {
    char *token = strtok(str, ",");
    while (token != NULL) {
        arr[*size] = atoi(token);
        (*size)++;
        token = strtok(NULL, ",");
    }
}

int main() {
    char str[] = "1,2,3,4,5";
    int arr[MAX_NUMBERS];
    int size = 0;

    convert_string_to_tuple(str, arr, &size);

    printf("Converted tuple: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
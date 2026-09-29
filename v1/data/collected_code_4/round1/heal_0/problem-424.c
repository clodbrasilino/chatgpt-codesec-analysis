#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* extractRearIndexElement(char* array[], int n) {
    char *result = malloc(sizeof(char) * n);
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        int len = strlen(array[i]);
        if (len > 0) {
            result[i] = array[i][len - 1];
        } else {
            printf("Empty string detected.\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

int main() {
    int n = 3;
    char* array[] = {"Hello", "World", "C"};
  
    char *result = extractRearIndexElement(array, n);

    for (int i = 0; i < n; i++) {
        printf("%c\n", result[i]);
    }

    free(result);

    return 0;
}

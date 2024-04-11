#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concatenate(char* tuple[], int size, char* delimiter) {
    int i;
    char* result = (char*)malloc(1000 * sizeof(char));
    strcpy(result, tuple[0]);

    for(i = 1; i < size; i++) {
        strcat(result, delimiter);
        strcat(result, tuple[i]);
    }

    return result;
}

int main() {
    char* tuple[] = {"Hello", "World", "from", "C"};
    char* delimiter = " ";
    char* result = concatenate(tuple, 4, delimiter);
    printf("%s\n", result);
    free(result);
    return 0;
}

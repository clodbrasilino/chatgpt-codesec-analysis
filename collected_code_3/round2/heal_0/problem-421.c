#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char* concatenate(char* tuple[], int size, char* delimiter) {
    static char result[MAX_SIZE];
    strcpy(result, tuple[0]);

    for(int i = 1; i < size; i++) {
        strcat(result, delimiter);
        strcat(result, tuple[i]);
    }

    return result;
}

int main() {
    char* tuple[] = {"Hello", "World", "C", "Programming"};
    char* delimiter = "-";
    char* result = concatenate(tuple, 4, delimiter);
    printf("%s\n", result);

    return 0;
}
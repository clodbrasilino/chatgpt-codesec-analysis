#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concatenate(char* str1, char* str2) {
    char* result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

int main() {
    char* str1 = "Hello";
    char* str2 = "World";
    char* result = concatenate(str1, str2);
    printf("%s\n", result);
    free(result);
    return 0;
}
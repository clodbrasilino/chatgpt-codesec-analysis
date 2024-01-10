#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str) {
    if (str == NULL || strlen(str) < 4)
        return;

    int len = strlen(str);

    char *start = strstr(str, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start++ = '\0';
    }
}

int main() {
    char* str = (char*) malloc(sizeof(char) * MAX_STRLEN);

    if (str == NULL){
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Enter a string: ");
    fgets(str, MAX_STRLEN, stdin);
    str[strcspn(str, "\n")] = '\0';
    abbreviateRoad(str);

    printf("Abbreviated string: %s\n", str);
    free(str);
    return 0;
}
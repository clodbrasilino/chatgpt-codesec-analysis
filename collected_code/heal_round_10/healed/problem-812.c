#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str) {
    if (str == NULL)
        return;

    size_t len = strnlen(str, MAX_STRLEN + 1);

    if (len <= 0 || len > MAX_STRLEN)
        return;

    char temp[MAX_STRLEN + 1];
    snprintf(temp, sizeof(temp), "%s", str);

    char *start = strstr(temp, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start = '\0';
    }

    size_t newLen = strnlen(temp, MAX_STRLEN);

    snprintf(str, newLen + 1, "%s", temp);
}

int main() {
    char* str = (char*) malloc(sizeof(char) * (MAX_STRLEN + 1));

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
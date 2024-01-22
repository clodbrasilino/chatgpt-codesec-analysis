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

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
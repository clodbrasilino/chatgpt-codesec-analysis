#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str, int len) {
    if (str == NULL || len < 4)
        return;

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[MAX_STRLEN+1];
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp, str, len);
    temp[len] = '\0';

    char *start = strstr(temp, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start = '\0';
    }

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(str, temp, len);
    str[len] = '\0';
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
    
    int len = strnlen(str, MAX_STRLEN);
    abbreviateRoad(str, len);

    printf("Abbreviated string: %s\n", str);
    free(str);
    return 0;
}
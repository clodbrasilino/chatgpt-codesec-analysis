#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str) {
    if (str == NULL)
        return;
    int len = strnlen(str, MAX_STRLEN);
    if (len < 4)
        return;

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[MAX_STRLEN+1] = {'\0'}; 
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, str, len);

    char *start = strstr(temp, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start++ = '\0';
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(str, temp, len + 1);
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

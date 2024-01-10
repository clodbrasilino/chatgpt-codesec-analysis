#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);

    for (int i = 0; i < len - 3; i++) {
        if (str[i] == 'r' && str[i+1] == 'o' && str[i+2] == 'a' && str[i+3] == 'd') {
            str[i+2] = 'd';
            str[i+3] = '.';
            str[i+4] = '\0';
            break;
        }
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
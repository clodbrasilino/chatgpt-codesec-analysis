#include<stdio.h>
#include<string.h>

void removeWhitespace(char *str) {
    if (!str) return;

    int i = 0, j = 0;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t size_of_str = strlen(str);

    for(i = 0; i < size_of_str; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {    
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101] = {0};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n')
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        str[strlen(str) - 1] = '\0';

    printf("Before removing whitespaces: %s\n", str);

    removeWhitespace(str);

    printf("After removing whitespaces: %s\n", str);

    return 0;
}
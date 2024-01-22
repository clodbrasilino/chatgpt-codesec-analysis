#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch, size_t max_size) {
    size_t count = max_size < SIZE ? max_size : SIZE - 1;
    for (size_t i = 0; i < count; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
    str[count] = '\0';
}

int main() {

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[SIZE] = "";
    char ch = '\0';
    size_t len = 0;

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        len = strcspn(str, "\n");
        if(len < sizeof(str)) {
            str[len] = '\0';
        }
    }

    printf("Enter the character to replace spaces with: "); 
    /* Possible weaknesses found:
     *   Check buffer boundaries if used in a loop including recursive loops  (CWE-120, CWE-20).
     */
    while ((getchar()) != '\n');
    scanf("%c", &ch);

    /* Possible weaknesses found:
     *  implicit declaration of function 'strnlen_s'; did you mean 'strnlen'? [-Wimplicit-function-declaration]
     */
    if(strnlen_s(str, SIZE)) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        replaceSpaces(str, ch, strlen(str));
    }

    printf("Modified string: %s\n", str);
    return 0;
}
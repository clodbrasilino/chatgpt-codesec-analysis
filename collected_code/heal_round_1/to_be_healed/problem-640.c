#include <stdio.h>
#include <string.h>

void remove_parenthesis_area(char* string) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int length = strlen(string);
    int i, j = 0;
    int count = 0;

    for (i = 0; i < length; i++) {
        if (string[i] == '(') {
            count++;
        }
        else if (string[i] == ')') {
            count--;
            if (count == 0) {
                continue;
            }
        }

        string[j++] = string[i];
    }

    string[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[100] = "This (is) a string (with) parenthesis.";
    remove_parenthesis_area(string);
    printf("%s\n", string);

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_LEN 102

int matchString(const char* str) {
    int i = 0;
    size_t len = strnlen(str, MAX_LEN);

    while (i < len - 2) {
        if (str[i]== 'a' && str[i + 2] == 'b') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LEN];
    printf("Enter a string: ");
    if(fgets(str, MAX_LEN, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        int result = matchString(str);
        if (result == 1) {
            printf("String matches the pattern.\n");
        } else {
            printf("String does not match the pattern.\n");
        }
    }
    return 0;
}
#include <stdio.h>
#include <ctype.h>

#define MAX_STR_LEN 101

void capitalizeFirstAndLastLetters(char *str) {
    if (str == NULL) 
        return;

    int len = 0;

    for (len = 0; str[len] != '\0' && len < MAX_STR_LEN - 1; ++len) {
        if (len == 0 || str[len - 1] == ' ') {
            str[len] = (char)toupper((unsigned char)str[len]);
        }
    }

    for (int i = 0; i < len; ++i) {
        if (isalpha((unsigned char)str[i]) && (i == len - 1 || str[i + 1] == ' ')) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LEN] = {'\0'};

    printf("Enter a string: ");

    if (fgets(str, sizeof(str), stdin) != NULL) {
        capitalizeFirstAndLastLetters(str);
        printf("Modified string: %s", str);
        return 0;
    }

    return -1;
}
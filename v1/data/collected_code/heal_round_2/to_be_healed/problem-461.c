#include <stdio.h>

int countUpperCaseChars(const char *str) {
    int count = 0;
    if (str == NULL){
        return count;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101] = {'\0'};
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    int result = countUpperCaseChars(str);
    printf("Number of upper case characters: %d\n", result);

    return 0;
}
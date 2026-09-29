#include<stdio.h>
#include<string.h>

#define MAX_SIZE 101

void removeChar(char* str, char c) {
    if(str == NULL)
        return;

    int count = 0;
    for (int i = 0; str[i] && i < MAX_SIZE; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = {'\0'};
    char c;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[2];

    printf("Enter a string: ");
    if(fgets(str, MAX_SIZE, stdin)) {
        str[strcspn(str, "\n")] = '\0';
    }

    printf("Enter the character to remove: ");
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if(fgets(temp, sizeof(temp), stdin)){
        c = temp[0];
        removeChar(str, c);
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'c' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}
#include<stdio.h>
#include<string.h>

#define MAX_INPUT 101

void splitString(const char str[], size_t strSize) {
    for(size_t i = 0; i < strSize; i++) {
        printf("%c ", str[i]);
    }   
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char input[MAX_INPUT + 1] = {0};
    printf("Enter a string: ");

    if(fgets(input, sizeof(input), stdin) != NULL) {
        size_t inputLength = strnlen(input, sizeof(input));
        if(inputLength > 0 && input[inputLength - 1] == '\n'){
            input[inputLength - 1] = '\0';
            inputLength--;
        }

        if(inputLength < MAX_INPUT) {
            printf("Individual characters: ");
            splitString(input, inputLength);
        }
        else {
            printf("Input string is too long");
        }
    }
   
    return 0;
}
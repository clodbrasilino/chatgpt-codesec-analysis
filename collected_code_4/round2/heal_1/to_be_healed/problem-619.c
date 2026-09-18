#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char *moveNumbersToString(const char *input) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    long inputLen = strlen(input);
    char *result = (char*)malloc((inputLen * sizeof(char)) + 1);

    if (!result) {
        perror("Failed to allocate memory for result string");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (long i = 0; i < inputLen; i++) {
        if (isdigit(input[i])) {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *input = "a1b2c3d4";
    char *result = moveNumbersToString(input);

    if (result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}
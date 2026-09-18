#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *moveNumbersToString(const char *input) {
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
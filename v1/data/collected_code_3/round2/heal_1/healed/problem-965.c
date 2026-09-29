#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camelToSnake(char* input) {
    int i = 0, j = 0;
    char* output = (char*)malloc(sizeof(char) * 256);

    if (!output) {
        return NULL;
    }

    while (input[i]) {
        if (isupper(input[i])) {
            output[j++] = '_';
            output[j] = tolower(input[i]);
        } else {
            output[j] = input[i];
        }
        i++;
        j++;
    }
    
    output[j] = '\0';
    return output;
}

int main() {
    char camelCaseString[] = "camelCaseString";
    char* snakeCaseString = camelToSnake(camelCaseString);

    if (!snakeCaseString) {
        return -1;
    }

    printf("%s\n", snakeCaseString);
    free(snakeCaseString);
    return 0;
}
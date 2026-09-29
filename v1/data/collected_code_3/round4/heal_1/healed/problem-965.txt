#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camelToSnake(char* input) {
    int i = 0, j = 0;
    char* output = (char*)malloc(sizeof(char) * 100);

    if(output == NULL) {
        return NULL;
    }

    while (input[i]) {
        if (isupper(input[i])) {
            output[j] = '_';
            j++;
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
    if(snakeCaseString == NULL) {
        printf("Memory allocation failed");
        return 1;
    }
    printf("%s\n", snakeCaseString);
    free(snakeCaseString);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* camel_to_snake(char* input) {
    int i, len, j = 0;
    len = strlen(input);
    char* output = (char*)malloc(sizeof(char) * (2 * len + 1));

    if (output == NULL) {
        return NULL;
    }
    for (i = 0; i < len; i++) {
        if (isupper(input[i])) {
            output[j++] = '_';
            output[j] = tolower(input[i]);
        } else {
            output[j] = input[i];
        }
        j++;
    }
    output[j] = '\0';

    return output;
}

int main() {
    char camelCase[] = "camelCaseString";
    char* snake_case = camel_to_snake(camelCase);

    if (snake_case != NULL) {
        printf("%s\n", snake_case);
        free(snake_case);
    }

    return 0;
}
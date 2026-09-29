#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *camel_to_snake_case(const char *input) {
    if (input == NULL)
        return NULL;

    int len = strlen(input);
    char *output = malloc(sizeof(char) * (len * 2));
    if (!output)
        return NULL;

    int j = 0;
    for (int i = 0; i < len; ++i) {
        if (isupper(input[i])) {
            output[j++] = '_';
            output[j++] = tolower(input[i]);
        } else {
            output[j++] = input[i];
        }
    }

    output = realloc(output, j + 1);
    if (!output)
        return NULL;

    output[j] = '\0';

    return output;
}

int main() {
    char *camelCase = "camelCaseString";
    char *snake_case = camel_to_snake_case(camelCase);

    if (snake_case != NULL) {
        printf("%s\n", snake_case);
        free(snake_case);
    } else {
        printf("error: memory allocation failed\n");
    }

    return 0;
}
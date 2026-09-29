#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *str) {
    int i = 0, j = 0, len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    while (str[j] == '_') j++; // Skip leading underscores
    result[i++] = toupper(str[j++]);

    for (; str[j]; j++) {
        if (str[j] == '_') {
            j++;
            if (str[j]) {
                result[i++] = toupper(str[j]);
            }
        } else {
            result[i++] = str[j];
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    char input[] = "python_program";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    char input2[] = "__programming_language";
    output = snake_to_camel(input2);
    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    char input3[] = "_python_language_";
    output = snake_to_camel(input3);
    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
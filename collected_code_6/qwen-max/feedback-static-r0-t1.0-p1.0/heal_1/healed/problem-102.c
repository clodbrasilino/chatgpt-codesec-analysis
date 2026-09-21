#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *str) {
    int i, len = strlen(str);
    char *result = malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    for (i = 0, result[0] = '\0'; *str; str++) {
        if (*str == '_') {
            str++;
            if (*str) {
                char temp[2];
                temp[0] = toupper(*str);
                temp[1] = '\0';
                strcat(result, temp);
            }
        } else {
            char temp[2];
            temp[0] = *str;
            temp[1] = '\0';
            strcat(result, temp);
        }
    }
    return result;
}

int main() {
    char input[] = "this_is_snake_case";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
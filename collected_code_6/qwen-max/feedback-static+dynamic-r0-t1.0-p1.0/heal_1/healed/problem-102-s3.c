#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    char *result = (char *)malloc(strlen(snake_str) + 1);
    int i, j = 0;
    for (i = 0; snake_str[i]; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (snake_str[i]) {
                result[j++] = toupper(snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char snake_case_str[] = "python_program";
    char *camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    free(camel_case_str);

    snake_case_str[0] = 'p';
    snake_case_str[1] = 'r';
    snake_case_str[2] = 'o';
    snake_case_str[3] = 'g';
    snake_case_str[4] = 'r';
    snake_case_str[5] = 'a';
    snake_case_str[6] = 'm';
    snake_case_str[7] = '_';
    snake_case_str[8] = 'l';
    snake_case_str[9] = 'a';
    snake_case_str[10] = 'n';
    snake_case_str[11] = 'g';
    snake_case_str[12] = 'u';
    snake_case_str[13] = 'a';
    snake_case_str[14] = 'g';
    snake_case_str[15] = 'e';
    snake_case_str[16] = '\0';

    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    free(camel_case_str);

    snprintf(snake_case_str, 17, "python_language");
    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    free(camel_case_str);

    return 0;
}
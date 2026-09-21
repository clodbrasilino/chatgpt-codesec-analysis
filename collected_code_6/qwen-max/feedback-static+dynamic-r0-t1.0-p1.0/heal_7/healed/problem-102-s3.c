#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *snake_str, size_t len) {
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (i < len) {
                result[j++] = toupper((unsigned char)snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char snake_case_str[16] = "python_program";
    if (strlen(snake_case_str) >= 15 || snake_case_str[15] != '\0') {
        fprintf(stderr, "Input string is too long\n");
        return 1;
    }
    size_t len = strlen(snake_case_str);
    char *camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    snprintf(snake_case_str, sizeof(snake_case_str), "program_language");
    if (strlen(snake_case_str) >= 15 || snake_case_str[15] != '\0') {
        fprintf(stderr, "Input string is too long\n");
        return 1;
    }
    len = strlen(snake_case_str);
    camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    snprintf(snake_case_str, sizeof(snake_case_str), "python_language");
    if (strlen(snake_case_str) >= 15 || snake_case_str[15] != '\0') {
        fprintf(stderr, "Input string is too long\n");
        return 1;
    }
    len = strlen(snake_case_str);
    camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    return 0;
}
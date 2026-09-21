#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    int len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) return NULL;
    int capitalize_next = 0;

    for (int i = 0, j = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next || (j == 0)) {
            camel_str[j++] = toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[len] = '\0';
    return camel_str;
}

int main() {
    char test0[] = "python_program";
    char *result0 = snake_to_camel(test0);
    printf("%s\n", result0);
    free(result0);

    char test1[] = "python_language";
    char *result1 = snake_to_camel(test1);
    printf("%s\n", result1);
    free(result1);

    char test2[] = "programming_language";
    char *result2 = snake_to_camel(test2);
    printf("%s\n", result2);
    free(result2);

    return 0;
}
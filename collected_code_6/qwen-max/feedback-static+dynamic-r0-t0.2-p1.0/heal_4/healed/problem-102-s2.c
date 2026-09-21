#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 1;
    size_t len = strlen(snake_str);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }
    int index = 0;

    while (index < len + 1) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next && isalpha(*p)) {
            output[index] = toupper(*p);
            capitalize_next = 0;
        } else {
            output[index] = *p;
        }
        index++;
        p++;
    }
    output[len] = '\0';
    return output;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    if (camel_case != NULL) {
        printf("%s\n", camel_case);
        free(camel_case);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_[a-z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[1];
    const char* cursor = snake_str;
    char* dest = camel_str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        
        size_t i;
        for (i = 0; i < prefix_len; i++) {
            dest[i] = cursor[i];
        }
        dest += prefix_len;
        
        *dest = toupper((unsigned char)cursor[pmatch[0].rm_so + 1]);
        dest++;
        
        cursor += pmatch[0].rm_eo;
    }

    while (*cursor != '\0') {
        *dest = *cursor;
        dest++;
        cursor++;
    }
    *dest = '\0';

    regfree(&regex);

    return camel_str;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Error converting string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
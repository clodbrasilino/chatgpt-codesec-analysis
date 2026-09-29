#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* str_copy = malloc(len + 1);
    char* result = malloc(len + 1);

    if (str_copy == NULL || result == NULL) {
        free(str_copy);
        free(result);
        regfree(&regex);
        return NULL;
    }

    strcpy(str_copy, snake_str);

    regmatch_t pmatch[2];
    char* p = str_copy;
    char* dest = result;

    while (regexec(&regex, p, 2, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_so;
        strncpy(dest, p, match_len);
        dest += match_len;

        *dest = toupper((unsigned char)p[pmatch[1].rm_so]);
        dest++;

        p += pmatch[0].rm_eo;
    }

    strcpy(dest, p);

    if (result[0] != '\0') {
        result[0] = toupper((unsigned char)result[0]);
    }

    free(str_copy);
    regfree(&regex);

    return result;
}

int main() {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t out_len = strlen(input) + 1;
    char* output = malloc(out_len);
    if (!output) {
        regfree(&regex);
        return NULL;
    }

    const char* cursor = input;
    char* out_ptr = output;
    regmatch_t matches[3];
    *out_ptr = '\0';

    while (regexec(&regex, cursor, 3, matches, 0) == 0) {
        size_t prefix_len = matches[1].rm_eo;
        size_t new_len = out_len + 1;
        char* new_output = realloc(output, new_len);
        if (!new_output) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = new_output;
        out_len = new_len;
        out_ptr = output + strlen(output);

        strncat(out_ptr, cursor, prefix_len);
        out_ptr += prefix_len;
        *out_ptr++ = '_';
        *out_ptr = '\0';

        cursor += matches[2].rm_so;
    }

    strcat(out_ptr, cursor);

    for (char* p = output; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }

    regfree(&regex);
    return output;
}

int main(void) {
    const char* camel = "thisIsCamelCaseString";
    char* snake = camel_to_snake(camel);
    
    if (snake) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Conversion failed.\n");
    }

    return 0;
}
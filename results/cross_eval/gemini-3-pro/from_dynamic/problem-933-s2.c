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

    regmatch_t pmatch[3];
    const char* cursor = input;
    size_t out_len = strlen(input) * 2 + 1;
    char* output = malloc(out_len);
    if (!output) {
        regfree(&regex);
        return NULL;
    }

    char* out_ptr = output;

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[1].rm_eo;
        memcpy(out_ptr, cursor, prefix_len);
        out_ptr += prefix_len;
        
        *out_ptr++ = '_';
        *out_ptr++ = tolower((unsigned char)cursor[pmatch[2].rm_so]);
        
        cursor += pmatch[2].rm_eo;
    }

    size_t remaining = strlen(cursor);
    memcpy(out_ptr, cursor, remaining);
    out_ptr += remaining;
    *out_ptr = '\0';

    regfree(&regex);

    for (char* p = output; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }

    return output;
}

int main(void) {
    const char* camel = "thisIsACamelCaseString";
    char* snake = camel_to_snake(camel);
    
    if (snake) {
        printf("Camel: %s\n", camel);
        printf("Snake: %s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Failed to convert string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
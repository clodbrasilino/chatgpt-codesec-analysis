#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char* camel_to_snake(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-z][A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_len = (strlen(input) * 2) + 1;
    char* output = (char*)malloc(max_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* cursor = input;
    regmatch_t pmatch[1];
    size_t out_idx = 0;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t copy_len = (size_t)pmatch[0].rm_so + 1;
        
        for (size_t i = 0; i < copy_len; i++) {
            output[out_idx++] = (char)tolower((unsigned char)cursor[i]);
        }
        
        output[out_idx++] = '_';
        output[out_idx++] = (char)tolower((unsigned char)cursor[copy_len]);
        
        cursor += pmatch[0].rm_eo;
    }

    while (*cursor != '\0') {
        output[out_idx++] = (char)tolower((unsigned char)*cursor);
        cursor++;
    }
    output[out_idx] = '\0';

    regfree(&regex);

    char* resized_output = (char*)realloc(output, out_idx + 1);
    if (resized_output != NULL) {
        return resized_output;
    }

    return output;
}

int main(void) {
    const char* test_strings[] = {
        "camelCase",
        "CamelCase",
        "myHTMLParser",
        "simpleTestString",
        ""
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char* snake = camel_to_snake(test_strings[i]);
        if (snake != NULL) {
            printf("%s\n", snake);
            free(snake);
        }
    }

    return 0;
}
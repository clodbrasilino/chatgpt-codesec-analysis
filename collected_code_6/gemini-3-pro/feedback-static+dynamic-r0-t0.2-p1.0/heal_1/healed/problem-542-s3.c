#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LEN 4096

char* replace_chars_with_colon(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti;
    
    reti = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_STR_LEN);
    if (input_len == MAX_STR_LEN) {
        regfree(&regex);
        return NULL; 
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    snprintf(result, input_len + 1, "%s", input);

    regmatch_t pmatch[1];
    char* cursor = result;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        cursor[pmatch[0].rm_so] = ':';
        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_str = "Hello, world. This is a test string.";
    
    char* modified_str = replace_chars_with_colon(test_str);
    
    if (modified_str != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", modified_str);
        free(modified_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
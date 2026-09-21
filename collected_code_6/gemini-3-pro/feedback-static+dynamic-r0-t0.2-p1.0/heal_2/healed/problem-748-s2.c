#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input_len < 1048576 && input[input_len] != '\0') {
        input_len++;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = input_len * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[3];
    const char* cursor = input;
    char* out_cursor = result;
    size_t remaining = max_len;

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[1].rm_eo;
        
        if (prefix_len >= remaining) {
            break;
        }
        
        for (size_t i = 0; i < prefix_len; i++) {
            out_cursor[i] = cursor[i];
        }
        
        out_cursor += prefix_len;
        remaining -= prefix_len;
        
        if (remaining > 0) {
            *out_cursor = ' ';
            out_cursor++;
            remaining--;
        }
        
        cursor += pmatch[1].rm_eo;
    }

    if (remaining > 0) {
        snprintf(out_cursor, remaining, "%s", cursor);
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* spaced_str = add_spaces(test_str);
    
    if (spaced_str != NULL) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
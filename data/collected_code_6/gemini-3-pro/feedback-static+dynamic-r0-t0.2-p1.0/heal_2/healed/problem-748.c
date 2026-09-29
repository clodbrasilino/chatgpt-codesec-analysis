#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces(const char* input) {
    if (!input) return NULL;

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, 1024 * 1024);
    size_t max_len = input_len * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[3];
    const char* cursor = input;
    char* out_cursor = result;
    *out_cursor = '\0';
    size_t remaining_space = max_len;

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[1].rm_eo;
        
        if (prefix_len >= remaining_space) {
            break;
        }

        memcpy(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;
        remaining_space -= prefix_len;
        
        if (remaining_space == 0) {
            break;
        }

        *out_cursor = ' ';
        out_cursor++;
        remaining_space--;
        
        cursor += pmatch[2].rm_so;
    }

    snprintf(out_cursor, remaining_space, "%s", cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* spaced_str = add_spaces(test_str);
    
    if (spaced_str) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_SIZE 8192

char* insert_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_INPUT_SIZE);
    if (input_len >= MAX_INPUT_SIZE) {
        regfree(&regex);
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
    *out_cursor = '\0';
    size_t remaining_dest_len = max_len;

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[1].rm_eo;
        
        if (prefix_len >= remaining_dest_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        for (size_t i = 0; i < prefix_len; i++) {
            out_cursor[i] = cursor[i];
        }
        
        out_cursor += prefix_len;
        remaining_dest_len -= prefix_len;
        
        if (remaining_dest_len <= 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        *out_cursor = ' ';
        out_cursor++;
        remaining_dest_len--;
        
        cursor += prefix_len;
    }

    size_t remaining_len = strnlen(cursor, MAX_INPUT_SIZE);
    
    if (remaining_len >= remaining_dest_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    for (size_t i = 0; i < remaining_len; i++) {
        out_cursor[i] = cursor[i];
    }
    out_cursor[remaining_len] = '\0';

    regfree(&regex);

    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* spaced_str = insert_spaces(test_str);
    
    if (spaced_str != NULL) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
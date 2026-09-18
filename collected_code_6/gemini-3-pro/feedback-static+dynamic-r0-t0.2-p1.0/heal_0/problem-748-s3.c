#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* insert_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = strlen(input) * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[3];
    const char* cursor = input;
    char* out_cursor = result;
    *out_cursor = '\0';

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[1].rm_eo;
        strncpy(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;
        
        *out_cursor = ' ';
        out_cursor++;
        
        cursor += prefix_len;
    }

    strcpy(out_cursor, cursor);
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
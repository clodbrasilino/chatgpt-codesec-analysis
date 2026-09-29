#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t new_str_len = input_len;
    
    for (size_t i = 1; i < input_len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            new_str_len++;
        }
    }

    char* result = (char*)malloc(new_str_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t j = 0;
    result[j++] = input[0];

    for (size_t i = 1; i < input_len; i++) {
        char current_char[2] = {input[i], '\0'};
        regmatch_t matches[1];
        reti = regexec(&regex, current_char, 1, matches, 0);
        
        if (!reti) {
            result[j++] = ' ';
        }
        result[j++] = input[i];
    }
    
    result[j] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "HelloWorldThisIsCTesting";
    char* spaced_string = add_spaces_before_capitals(test_string);

    if (spaced_string != NULL) {
        printf("%s\n", spaced_string);
        free(spaced_string);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}
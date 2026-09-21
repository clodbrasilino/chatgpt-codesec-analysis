#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_uppercase_lowercase_sequences(const char *input_string);

void find_uppercase_lowercase_sequences(const char *input_string) {
    regex_t regex;
    int compile_status;
    regmatch_t match[1];
    const char *cursor;

    if (input_string == NULL) {
        return;
    }

    compile_status = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (compile_status != 0) {
        size_t err_size = regerror(compile_status, &regex, NULL, 0);
        char *error_buffer = (char *)malloc(err_size);
        if (error_buffer != NULL) {
            regerror(compile_status, &regex, error_buffer, err_size);
            fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
            free(error_buffer);
        }
        return;
    }

    cursor = input_string;
    while (1) {
        int execute_status = regexec(&regex, cursor, 1, match, 0);
        
        if (execute_status == 0) {
            int length = match[0].rm_eo - match[0].rm_so;
            printf("%.*s\n", length, cursor + match[0].rm_so);
            cursor += match[0].rm_eo;
        } else if (execute_status == REG_NOMATCH) {
            break;
        } else {
            size_t err_size = regerror(execute_status, &regex, NULL, 0);
            char *error_buffer = (char *)malloc(err_size);
            if (error_buffer != NULL) {
                regerror(execute_status, &regex, error_buffer, err_size);
                fprintf(stderr, "Regex execution error: %s\n", error_buffer);
                free(error_buffer);
            }
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *test_text = "Finding Sequences In This String Like CamelCase Or Regular Words.";
    
    find_uppercase_lowercase_sequences(test_text);
    
    return 0;
}
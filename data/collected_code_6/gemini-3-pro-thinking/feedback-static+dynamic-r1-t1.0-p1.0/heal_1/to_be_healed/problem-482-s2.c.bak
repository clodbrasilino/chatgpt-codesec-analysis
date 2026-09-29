#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_uppercase_lowercase_sequences(const char *input_string);

void find_uppercase_lowercase_sequences(const char *input_string) {
    regex_t regex;
    int compile_status;
    /* Possible weaknesses found:
     *  The scope of the variable 'execute_status' can be reduced. [variableScope]
     */
    int execute_status;
    regmatch_t match[1];
    const char *cursor;
    char error_buffer[256];

    if (input_string == NULL) {
        return;
    }

    compile_status = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (compile_status != 0) {
        regerror(compile_status, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    cursor = input_string;
    while (1) {
        execute_status = regexec(&regex, cursor, 1, match, 0);
        
        if (execute_status == 0) {
            int length = match[0].rm_eo - match[0].rm_so;
            printf("%.*s\n", length, cursor + match[0].rm_so);
            cursor += match[0].rm_eo;
        } else if (execute_status == REG_NOMATCH) {
            break;
        } else {
            regerror(execute_status, &regex, error_buffer, sizeof(error_buffer));
            fprintf(stderr, "Regex execution error: %s\n", error_buffer);
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
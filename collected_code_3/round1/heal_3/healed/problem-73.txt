#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string_by_regex(char *str, char *regex_pattern) {
    char **result = NULL;
    size_t count = 0;
    regex_t regex_comp;
    regmatch_t group_array[2];
    char *cursor;

    if (regcomp(&regex_comp, regex_pattern, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return NULL;
    }

    cursor = str;

    while (!regexec(&regex_comp, cursor, 2, group_array, 0)) {
        int start = group_array[0].rm_so;
        int end = group_array[0].rm_eo;
        char *token = strndup(cursor + start, end - start);

        if (token == NULL) {
            for(int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }

        cursor += end;

        char **temp = realloc(result, sizeof(char*) * (count + 2));
        if (temp == NULL) {
            free(token);
            for(int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        
        result = temp;
        result[count++] = token;
        result[count] = NULL;
    }

    regfree(&regex_comp);
    return result;
}

int main() {
    char **tokens;
    char str[] = "Hello, World! This is a test.";
    char regex_pattern[] = "\\s+|,\\s*|\\.\\s*";
    
    tokens = split_string_by_regex(str, regex_pattern);
    if (tokens) {
        for (int i = 0; tokens[i]; i++) {
            printf("'%s'\n", tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }
    return 0;
}
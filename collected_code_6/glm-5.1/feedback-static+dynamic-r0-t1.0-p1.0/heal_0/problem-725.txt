#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **extract_quoted(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[1];
    int reti;
    char **results = NULL;
    size_t capacity = 0;
    *count = 0;

    reti = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (reti != 0) {
        return NULL;
    }

    const char *p = str;
    while (1) {
        reti = regexec(&regex, p, 1, matches, 0);
        if (reti == REG_NOMATCH) {
            break;
        }
        if (reti != 0) {
            regfree(&regex);
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            *count = 0;
            return NULL;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **temp = realloc(results, capacity * sizeof(char *));
            if (!temp) {
                regfree(&regex);
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                *count = 0;
                return NULL;
            }
            results = temp;
        }

        size_t start = matches[0].rm_so + 1; 
        size_t end = matches[0].rm_eo - 1;   
        size_t len = end - start;

        char *substr = malloc(len + 1);
        if (!substr) {
            regfree(&regex);
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            *count = 0;
            return NULL;
        }

        memcpy(substr, p + start, len);
        substr[len] = '\0';

        results[*count] = substr;
        (*count)++;

        p += matches[0].rm_eo;
    }

    regfree(&regex);
    return results;
}

int main(void) {
    const char *input = "Extract \"this value\" and \"that value\" from the string.";
    size_t count = 0;
    
    char **values = extract_quoted(input, &count);
    
    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }
    
    return 0;
}
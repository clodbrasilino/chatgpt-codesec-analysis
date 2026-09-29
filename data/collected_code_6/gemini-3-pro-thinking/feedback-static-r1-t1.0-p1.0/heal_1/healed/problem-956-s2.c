#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void free_string_array(char **array, int count) {
    if (!array) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

char **split_at_uppercase(const char *str, int *out_count) {
    if (!str || !out_count) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    char **result = malloc((size_t)capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = str;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(result, (size_t)capacity * sizeof(char *));
            if (!temp) {
                free_string_array(result, count);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        size_t len = (size_t)match[0].rm_so;
        
        result[count] = strndup(cursor, len);
        if (!result[count]) {
            free_string_array(result, count);
            regfree(&regex);
            return NULL;
        }

        count++;
        cursor += match[0].rm_eo;
    }

    if (count >= capacity) {
        char **temp = realloc(result, ((size_t)count + 1) * sizeof(char *));
        if (!temp) {
            free_string_array(result, count);
            regfree(&regex);
            return NULL;
        }
        result = temp;
    }

    result[count] = strdup(cursor);
    if (!result[count]) {
        free_string_array(result, count);
        regfree(&regex);
        return NULL;
    }
    count++;

    *out_count = count;
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "splitThisStringAtUppercaseLetters";
    int count = 0;
    
    char **parts = split_at_uppercase(test_str, &count);
    if (!parts) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
    }

    free_string_array(parts, count);
    return 0;
}
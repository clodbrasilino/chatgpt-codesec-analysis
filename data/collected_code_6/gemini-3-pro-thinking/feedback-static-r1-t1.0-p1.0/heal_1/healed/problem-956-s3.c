#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void free_split_results(char **results, size_t count) {
    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(results[i]);
        }
        free(results);
    }
}

char **split_at_uppercase(const char *str, size_t *out_count) {
    if (str == NULL || out_count == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    char **results = NULL;
    size_t count = 0;
    const char *cursor = str;
    regmatch_t pmatch[1];
    char *segment = NULL;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        char **temp_results = realloc(results, (count + 1) * sizeof(char *));
        if (temp_results == NULL) {
            goto cleanup;
        }
        results = temp_results;

        size_t len = (size_t)pmatch[0].rm_so;
        segment = malloc(len + 1);
        if (segment == NULL) {
            goto cleanup;
        }
        
        if (len > 0) {
            for (size_t i = 0; i < len; i++) {
                segment[i] = cursor[i];
            }
        }
        segment[len] = '\0';
        results[count] = segment;
        count++;
        segment = NULL;

        cursor += pmatch[0].rm_eo;
    }

    char **temp_results = realloc(results, (count + 1) * sizeof(char *));
    if (temp_results == NULL) {
        goto cleanup;
    }
    results = temp_results;

    size_t rem_len = 0;
    while (cursor[rem_len] != '\0') {
        rem_len++;
    }
    
    segment = malloc(rem_len + 1);
    if (segment == NULL) {
        goto cleanup;
    }
    
    if (rem_len > 0) {
        for (size_t i = 0; i < rem_len; i++) {
            segment[i] = cursor[i];
        }
    }
    segment[rem_len] = '\0';
    results[count] = segment;
    count++;

    regfree(&regex);
    *out_count = count;
    return results;

cleanup:
    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(results[i]);
        }
        free(results);
    }
    regfree(&regex);
    return NULL;
}

int main(void) {
    const char *test_str = "splitThisStringAtUppercaseLetters";
    size_t count = 0;
    
    char **parts = split_at_uppercase(test_str, &count);
    
    if (parts != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
        }
        free_split_results(parts, count);
    }
    
    return 0;
}
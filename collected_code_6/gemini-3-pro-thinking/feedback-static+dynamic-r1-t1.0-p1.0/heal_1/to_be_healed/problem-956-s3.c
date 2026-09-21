#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(segment, cursor, len);
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t rem_len = strlen(cursor);
    segment = malloc(rem_len + 1);
    if (segment == NULL) {
        goto cleanup;
    }
    
    if (rem_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(segment, cursor, rem_len);
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

void free_split_results(char **results, size_t count) {
    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(results[i]);
        }
        free(results);
    }
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
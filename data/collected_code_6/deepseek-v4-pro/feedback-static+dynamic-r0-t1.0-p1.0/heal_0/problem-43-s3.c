#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_lowercase_underscore_sequences(const char *input, char ***matches, size_t *match_count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[a-z]+_[a-z]+";
    int ret;
    size_t count = 0;
    size_t capacity = 10;
    char **result;
    const char *cursor;
    int status;

    if (input == NULL || matches == NULL || match_count == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return -1;
    }

    cursor = input;
    status = regexec(&regex, cursor, 1, pmatch, 0);
    while (status == 0) {
        regoff_t start = pmatch[0].rm_so;
        regoff_t end = pmatch[0].rm_eo;
        size_t len = (size_t)(end - start);

        if (count >= capacity) {
            char **new_result;
            size_t new_capacity = capacity * 2;
            new_result = realloc(result, new_capacity * sizeof(char *));
            if (new_result == NULL) {
                size_t i;
                for (i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = new_result;
            capacity = new_capacity;
        }

        result[count] = malloc(len + 1);
        if (result[count] == NULL) {
            size_t i;
            for (i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }
        memcpy(result[count], cursor + start, len);
        result[count][len] = '\0';
        count++;

        cursor += end;
        if (*cursor == '\0') {
            break;
        }
        status = regexec(&regex, cursor, 1, pmatch, 0);
    }

    if (count == 0) {
        free(result);
        result = NULL;
    }

    *matches = result;
    *match_count = count;
    regfree(&regex);
    return 0;
}

void free_matches(char **matches, size_t match_count) {
    size_t i;
    if (matches == NULL) {
        return;
    }
    for (i = 0; i < match_count; i++) {
        free(matches[i]);
    }
    free(matches);
}

int main(void) {
    const char *test_string = "hello_world foo_bar test abc_def_ghi x_y_z test1_abc";
    char **matches = NULL;
    size_t match_count = 0;
    size_t i;
    int ret;

    ret = find_lowercase_underscore_sequences(test_string, &matches, &match_count);
    if (ret != 0) {
        fprintf(stderr, "Error finding matches\n");
        return 1;
    }

    printf("Found %zu matches:\n", match_count);
    for (i = 0; i < match_count; i++) {
        printf("%s\n", matches[i]);
    }

    free_matches(matches, match_count);
    return 0;
}
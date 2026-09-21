#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_first_repeated_word(const char *str) {
    if (str == NULL) {
        char *none_res = malloc(5);
        if (none_res != NULL) {
            snprintf(none_res, 5, "None");
        }
        return none_res;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *str_copy = malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }

    snprintf(str_copy, len + 1, "%s", str);

    char **seen_words = malloc((len + 1) * sizeof(char *));
    if (seen_words == NULL) {
        free(str_copy);
        return NULL;
    }

    size_t count = 0;
    char *result = NULL;
    char *token = strtok(str_copy, " \t\n\r,.;:!?()[]{}");

    while (token != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (strcmp(seen_words[i], token) == 0) {
                size_t res_len = 0;
                while (token[res_len] != '\0') {
                    res_len++;
                }
                result = malloc(res_len + 1);
                if (result != NULL) {
                    snprintf(result, res_len + 1, "%s", token);
                }
                goto cleanup;
            }
        }
        seen_words[count++] = token;
        token = strtok(NULL, " \t\n\r,.;:!?()[]{}");
    }

cleanup:
    free(seen_words);
    free(str_copy);

    if (result == NULL) {
        result = malloc(5);
        if (result != NULL) {
            snprintf(result, 5, "None");
        }
    }

    return result;
}

int main(void) {
    const char *text1 = "apple banana orange apple grape banana";
    char *repeated1 = find_first_repeated_word(text1);

    if (repeated1 != NULL) {
        printf("%s\n", repeated1);
        free(repeated1);
    }

    const char *text2 = "cat dog bird fish";
    char *repeated2 = find_first_repeated_word(text2);

    if (repeated2 != NULL) {
        printf("%s\n", repeated2);
        free(repeated2);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_words(const char *str, size_t *out_count) {
    regex_t regex;
    regmatch_t matches[1];
    int ret;
    char **result = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    const char *cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        *out_count = 0;
        return NULL;
    }

    while (regexec(&regex, cursor, 1, matches, 0) == 0) {
        if (matches[0].rm_so == -1) {
            break;
        }

        if (count >= capacity) {
            capacity = (capacity == 0) ? 10 : capacity * 2;
            char **temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                *out_count = 0;
                return NULL;
            }
            result = temp;
        }

        size_t len = matches[0].rm_eo - matches[0].rm_so;
        char *word = malloc(len + 1);
        if (word == NULL) {
            for (size_t i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *out_count = 0;
            return NULL;
        }

        memcpy(word, cursor + matches[0].rm_so, len);
        word[len] = '\0';

        result[count] = word;
        count++;

        cursor += matches[0].rm_eo;
        if (matches[0].rm_eo == 0) {
            cursor++;
        }
    }

    regfree(&regex);
    *out_count = count;
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    size_t count = 0;
    char **words = find_words(argv[1], &count);

    if (words != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
        free(words);
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_WORD_LEN 256

char **find_words(const char *input, int *count) {
    regex_t regex;
    regmatch_t match;
    char **words = NULL;
    int ret;
    size_t offset = 0;
    size_t input_len;
    int capacity = 10;
    *count = 0;

    if (!input) {
        return NULL;
    }

    input_len = strnlen(input, MAX_WORD_LEN * MAX_MATCHES);

    words = (char **)malloc(capacity * sizeof(char *));
    if (!words) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:alnum:]]{4,}", REG_EXTENDED);
    if (ret) {
        free(words);
        return NULL;
    }

    while (offset < input_len && input[offset] != '\0') {
        ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            for (int i = 0; i < *count; i++) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }

        size_t start = offset + (size_t)match.rm_so;
        size_t end = offset + (size_t)match.rm_eo;
        size_t len = end - start;

        if (len >= 4 && len < MAX_WORD_LEN) {
            if (start >= input_len || end > input_len || start + len != end) {
                regfree(&regex);
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }

            if (*count >= capacity) {
                capacity *= 2;
                if (capacity > MAX_MATCHES) {
                    regfree(&regex);
                    for (int i = 0; i < *count; i++) {
                        free(words[i]);
                    }
                    free(words);
                    return NULL;
                }
                char **temp = (char **)realloc(words, capacity * sizeof(char *));
                if (!temp) {
                    regfree(&regex);
                    for (int i = 0; i < *count; i++) {
                        free(words[i]);
                    }
                    free(words);
                    return NULL;
                }
                words = temp;
            }

            words[*count] = (char *)malloc(len + 1);
            if (!words[*count]) {
                regfree(&regex);
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }

            if (len + 1 <= len) {
                free(words[*count]);
                regfree(&regex);
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(words[*count], input + start, len);
            words[*count][len] = '\0';
            (*count)++;
        }

        offset = end;
        if (match.rm_eo == 0) {
            offset++;
        }
    }

    regfree(&regex);
    return words;
}

int main(void) {
    const char *text = "Hello world, this is a test of regex matching for words.";
    int count = 0;
    char **words = find_words(text, &count);

    if (!words) {
        fprintf(stderr, "Error processing text\n");
        return 1;
    }

    printf("Found %d words:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}
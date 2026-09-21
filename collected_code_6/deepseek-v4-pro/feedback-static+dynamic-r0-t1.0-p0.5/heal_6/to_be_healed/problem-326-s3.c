#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static size_t safe_strlen(const char* str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char* safe_strdup(const char* str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = safe_strlen(str, max_len);
    char* copy = (char*)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    copy[len] = '\0';
    return copy;
}

/* Possible weaknesses found:
 *  Parameter 'strings' can be declared as const array [constParameter]
 */
char* most_frequent_word(char* strings[], int size) {
    if (size <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount words[MAX_WORDS];
    int word_count = 0;

    for (int i = 0; i < size; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = safe_strlen(strings[i], MAX_WORD_LEN * MAX_WORDS - 1);
        char* str_copy = safe_strdup(strings[i], str_len);
        if (str_copy == NULL) {
            continue;
        }

        char* saveptr = NULL;
        char* token = strtok_r(str_copy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        while (token != NULL) {
            size_t token_len = safe_strlen(token, MAX_WORD_LEN - 1);

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, token, MAX_WORD_LEN - 1) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                size_t copy_len = token_len;
                if (copy_len >= MAX_WORD_LEN) {
                    copy_len = MAX_WORD_LEN - 1;
                }
                
                if (copy_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(words[word_count].word, token, copy_len);
                }
                words[word_count].word[copy_len] = '\0';
                words[word_count].count = 1;
                word_count++;
            }

            token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        }

        free(str_copy);
    }

    if (word_count == 0) {
        return NULL;
    }

    int max_index = 0;
    for (int i = 1; i < word_count; i++) {
        if (words[i].count > words[max_index].count) {
            max_index = i;
        }
    }

    size_t result_len = safe_strlen(words[max_index].word, MAX_WORD_LEN - 1);
    char* result = safe_strdup(words[max_index].word, result_len);
    return result;
}

int main() {
    char* strings[] = {
        "hello world hello",
        "foo bar foo foo",
        "hello foo world"
    };

    int size = sizeof(strings) / sizeof(strings[0]);
    char* result = most_frequent_word(strings, size);

    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}
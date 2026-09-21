#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static char *duplicate_string(const char *source, size_t length) {
    if (source == NULL) {
        return NULL;
    }
    
    size_t safe_length = (length < MAX_WORD_LEN - 1) ? length : MAX_WORD_LEN - 1;
    
    char *copy = malloc(safe_length + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    if (safe_length > 0) {
        memcpy(copy, source, safe_length);
    }
    copy[safe_length] = '\0';
    return copy;
}

static int is_delimiter(int c) {
    return isspace(c) || strchr(".,;:!?\"'()[]{}", c) != NULL;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *most_frequent_word(const char * const strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = calloc((size_t)MAX_WORDS, sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    char result[MAX_WORD_LEN] = {0};

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = safe_strlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        if (str_len == 0 || str_len >= (size_t)(MAX_WORD_LEN * MAX_WORDS)) {
            continue;
        }

        size_t safe_str_len = (str_len < (size_t)(MAX_WORD_LEN * MAX_WORDS - 1)) 
                            ? str_len 
                            : (size_t)(MAX_WORD_LEN * MAX_WORDS - 1);
        
        char *str_copy = malloc(safe_str_len + 1);
        if (str_copy == NULL) {
            continue;
        }

        memcpy(str_copy, strings[i], safe_str_len);
        str_copy[safe_str_len] = '\0';

        char *saveptr = NULL;
        char *token = strtok_r(str_copy, " \t\n\r", &saveptr);
        while (token != NULL) {
            size_t token_len = safe_strlen(token, MAX_WORD_LEN - 1);
            if (token_len == 0) {
                token = strtok_r(NULL, " \t\n\r", &saveptr);
                continue;
            }

            while (token_len > 0 && is_delimiter((unsigned char)token[token_len - 1])) {
                token_len--;
            }

            if (token_len == 0) {
                token = strtok_r(NULL, " \t\n\r", &saveptr);
                continue;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, token, MAX_WORD_LEN - 1) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        size_t copy_len = safe_strlen(words[j].word, MAX_WORD_LEN - 1);
                        size_t safe_copy = (copy_len < MAX_WORD_LEN - 1) ? copy_len : MAX_WORD_LEN - 1;
                        memcpy(result, words[j].word, safe_copy);
                        result[safe_copy] = '\0';
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                size_t copy_len = (token_len < MAX_WORD_LEN - 1) ? token_len : MAX_WORD_LEN - 1;
                
                memcpy(words[word_count].word, token, copy_len);
                words[word_count].word[copy_len] = '\0';
                words[word_count].count = 1;
                
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    memcpy(result, words[word_count].word, copy_len);
                    result[copy_len] = '\0';
                }
                word_count++;
            }

            token = strtok_r(NULL, " \t\n\r", &saveptr);
        }

        free(str_copy);
    }

    free(words);

    if (result[0] != '\0') {
        size_t result_len = safe_strlen(result, MAX_WORD_LEN - 1);
        return duplicate_string(result, result_len);
    }

    return NULL;
}

int main(void) {
    const char *test_strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };

    char *result = most_frequent_word(test_strings, 4);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
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
    if (len >= max_len) {
        return NULL;
    }
    char* copy = (char*)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        if (len + 1 > len + 1) {
            free(copy);
            return NULL;
        }
        memcpy(copy, str, len);
        copy[len] = '\0';
    } else {
        copy[0] = '\0';
    }
    return copy;
}

static void safe_word_copy(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    size_t src_len = safe_strlen(src, dest_size);
    size_t copy_len = src_len;
    if (copy_len >= dest_size) {
        copy_len = dest_size - 1;
    }
    if (copy_len > 0) {
        if (copy_len > dest_size - 1) {
            copy_len = dest_size - 1;
        }
        memcpy(dest, src, copy_len);
    }
    if (copy_len < dest_size) {
        dest[copy_len] = '\0';
    } else {
        dest[dest_size - 1] = '\0';
    }
}

static int is_delimiter(char c, const char* delimiters) {
    if (delimiters == NULL) {
        return 0;
    }
    size_t delim_len = safe_strlen(delimiters, 256);
    for (size_t i = 0; i < delim_len; i++) {
        if (c == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

static char* safe_strtok_r(char* str, const char* delimiters, char** saveptr) {
    if (delimiters == NULL || saveptr == NULL) {
        return NULL;
    }
    
    char* token_start;
    if (str != NULL) {
        token_start = str;
    } else if (*saveptr != NULL) {
        token_start = *saveptr;
    } else {
        return NULL;
    }
    
    while (*token_start != '\0' && is_delimiter(*token_start, delimiters)) {
        token_start++;
    }
    
    if (*token_start == '\0') {
        *saveptr = NULL;
        return NULL;
    }
    
    char* token_end = token_start;
    while (*token_end != '\0' && !is_delimiter(*token_end, delimiters)) {
        token_end++;
    }
    
    if (*token_end != '\0') {
        *token_end = '\0';
        *saveptr = token_end + 1;
    } else {
        *saveptr = NULL;
    }
    
    return token_start;
}

char* most_frequent_word(const char* const strings[], int size) {
    if (size <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount words[MAX_WORDS];
    int word_count = 0;

    for (int i = 0; i < size; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = safe_strlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        if (str_len >= (size_t)(MAX_WORD_LEN * MAX_WORDS)) {
            continue;
        }

        size_t buf_size = str_len + 1;
        if (buf_size == 0 || buf_size > MAX_WORD_LEN * MAX_WORDS) {
            continue;
        }

        char* str_copy = safe_strdup(strings[i], buf_size);
        if (str_copy == NULL) {
            continue;
        }

        char* saveptr = NULL;
        char* token = safe_strtok_r(str_copy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        while (token != NULL) {
            size_t token_len = safe_strlen(token, MAX_WORD_LEN);
            if (token_len == 0 || token_len >= MAX_WORD_LEN) {
                token = safe_strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
                continue;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, token, MAX_WORD_LEN - 1) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                safe_word_copy(words[word_count].word, token, MAX_WORD_LEN);
                words[word_count].count = 1;
                word_count++;
            }

            token = safe_strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
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

    size_t result_len = safe_strlen(words[max_index].word, MAX_WORD_LEN);
    if (result_len == 0 || result_len >= MAX_WORD_LEN) {
        return NULL;
    }

    char* result = safe_strdup(words[max_index].word, result_len + 1);
    return result;
}

int main() {
    const char* strings[] = {
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
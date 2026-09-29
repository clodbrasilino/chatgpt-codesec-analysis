#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *copy_string(const char *src, size_t len) {
    if (!src) {
        return NULL;
    }
    
    char *dest = malloc(len + 1);
    if (dest) {
        for (size_t i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest[len] = '\0';
    }
    
    return dest;
}

char *find_first_repeated_word(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t capacity = 16;
    char **seen_words = malloc(capacity * sizeof(char *));
    if (!seen_words) {
        return NULL;
    }

    size_t seen_count = 0;
    char *result = NULL;
    const char *delims = " \t\n\r\v\f.,;!?";
    const char *p = str;

    while (*p) {
        p += strspn(p, delims);
        if (!*p) {
            break;
        }

        size_t word_len = strcspn(p, delims);
        char *current_word = copy_string(p, word_len);
        
        if (!current_word) {
            goto cleanup;
        }

        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_words[i], current_word) == 0) {
                result = current_word;
                goto cleanup;
            }
        }

        if (seen_count >= capacity) {
            size_t new_capacity = capacity * 2;
            char **new_seen_words = realloc(seen_words, new_capacity * sizeof(char *));
            if (!new_seen_words) {
                free(current_word);
                goto cleanup;
            }
            seen_words = new_seen_words;
            capacity = new_capacity;
        }

        seen_words[seen_count++] = current_word;
        p += word_len;
    }

cleanup:
    for (size_t i = 0; i < seen_count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);
    
    return result;
}

int main(void) {
    const char *text = "This is a test and this test is only a test";
    char *repeated = find_first_repeated_word(text);

    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found\n");
    }

    return 0;
}
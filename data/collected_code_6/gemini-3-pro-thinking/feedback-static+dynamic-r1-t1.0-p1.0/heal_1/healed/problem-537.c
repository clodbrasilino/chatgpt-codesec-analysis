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
        char *none_str = malloc(5);
        if (none_str) {
            none_str[0] = 'N';
            none_str[1] = 'o';
            none_str[2] = 'n';
            none_str[3] = 'e';
            none_str[4] = '\0';
        }
        return none_str;
    }

    size_t capacity = 16;
    char **seen_words = malloc(capacity * sizeof(char *));
    if (!seen_words) {
        char *none_str = malloc(5);
        if (none_str) {
            none_str[0] = 'N';
            none_str[1] = 'o';
            none_str[2] = 'n';
            none_str[3] = 'e';
            none_str[4] = '\0';
        }
        return none_str;
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
            capacity *= 2;
            char **tmp = realloc(seen_words, capacity * sizeof(char *));
            if (!tmp) {
                free(current_word);
                goto cleanup;
            }
            seen_words = tmp;
        }

        seen_words[seen_count++] = current_word;
        p += word_len;
    }

cleanup:
    for (size_t i = 0; i < seen_count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);
    
    if (!result) {
        result = malloc(5);
        if (result) {
            result[0] = 'N';
            result[1] = 'o';
            result[2] = 'n';
            result[3] = 'e';
            result[4] = '\0';
        }
    }
    
    return result;
}

int main(void) {
    const char *text = "This is a test and this test is only a test";
    char *repeated = find_first_repeated_word(text);

    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    }

    return 0;
}
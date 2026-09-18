#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *copy_string(const char *src, size_t len) {
    if (!src) {
        return NULL;
    }
    
    char *dest = malloc(len + 1);
    if (dest) {
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    
    return dest;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char *find_first_repeated_word(const char *str) {
    if (!str) {
        return copy_string("None", 4);
    }

    size_t len = strlen(str);
    size_t max_words = (len / 2) + 1;
    
    char **seen_words = calloc(max_words, sizeof(char *));
    if (!seen_words) {
        return copy_string("None", 4);
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

        seen_words[seen_count++] = current_word;
        p += word_len;
    }

cleanup:
    for (size_t i = 0; i < seen_count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);
    
    if (!result) {
        result = copy_string("None", 4);
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
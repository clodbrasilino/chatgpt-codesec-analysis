#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static char *copy_word(const char *start, size_t length)
{
    char *word = malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }
    memcpy(word, start, length);
    word[length] = '\0';
    return word;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  */

char *find_first_repeated_word(const char *str)
{
    char **seen_words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *p;
    char *result = NULL;

    if (str == NULL) {
        return NULL;
    }

    p = str;

    while (*p != '\0') {
        const char *start;
        size_t length;
        size_t i;
        int found = 0;

        while (*p != '\0' && !is_word_char((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        start = p;
        while (*p != '\0' && is_word_char((unsigned char)*p)) {
            p++;
        }
        length = (size_t)(p - start);

        for (i = 0; i < count; i++) {
            if (strlen(seen_words[i]) == length &&
                memcmp(seen_words[i], start, length) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            result = copy_word(start, length);
            break;
        }

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            char **new_array = realloc(seen_words,
                                       new_capacity * sizeof(*new_array));
            if (new_array == NULL) {
                break;
            }
            seen_words = new_array;
            capacity = new_capacity;
        }

        seen_words[count] = copy_word(start, length);
        if (seen_words[count] == NULL) {
            break;
        }
        count++;
    }

    for (size_t i = 0; i < count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "the quick brown fox jumps over the lazy dog",
        "hello world, hello everyone",
        "no repeated words here",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        char *word = find_first_repeated_word(tests[t]);
        printf("Input: \"%s\"\n", tests[t]);
        if (word != NULL) {
            printf("First repeated word: \"%s\"\n\n", word);
            free(word);
        } else {
            printf("No repeated word found.\n\n");
        }
    }

    return 0;
}
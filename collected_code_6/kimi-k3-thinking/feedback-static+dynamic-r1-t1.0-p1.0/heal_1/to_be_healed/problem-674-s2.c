#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static int is_space_char(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int word_seen(char **seen, size_t count, const char *word)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (strcmp(seen[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input)
{
    char **seen = NULL;
    char *result = NULL;
    size_t seen_count = 0;
    size_t seen_capacity = 0;
    size_t result_len = 0;
    size_t input_len;
    size_t pos = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    seen_capacity = INITIAL_CAPACITY;
    seen = malloc(seen_capacity * sizeof(*seen));
    if (seen == NULL) {
        free(result);
        return NULL;
    }

    while (pos < input_len) {
        size_t start;
        size_t word_len;
        char *word;

        while (pos < input_len && is_space_char(input[pos])) {
            pos++;
        }
        if (pos >= input_len) {
            break;
        }

        start = pos;
        while (pos < input_len && !is_space_char(input[pos])) {
            pos++;
        }
        word_len = pos - start;

        word = malloc(word_len + 1);
        if (word == NULL) {
            goto fail;
        }
        memcpy(word, input + start, word_len);
        word[word_len] = '\0';

        if (word_seen(seen, seen_count, word)) {
            free(word);
        } else {
            if (seen_count == seen_capacity) {
                size_t new_capacity = seen_capacity * 2;
                char **new_seen = realloc(seen, new_capacity * sizeof(*new_seen));
                if (new_seen == NULL) {
                    free(word);
                    goto fail;
                }
                seen = new_seen;
                seen_capacity = new_capacity;
            }
            seen[seen_count++] = word;

            if (result_len > 0) {
                result[result_len++] = ' ';
            }
            memcpy(result + result_len, word, word_len);
            result_len += word_len;
            result[result_len] = '\0';
        }
    }

    for (i = 0; i < seen_count; i++) {
        free(seen[i]);
    }
    free(seen);
    return result;

fail:
    for (i = 0; i < seen_count; i++) {
        free(seen[i]);
    }
    free(seen);
    free(result);
    return NULL;
}

int main(void)
{
    const char *tests[] = {
        "the quick brown fox jumps over the lazy dog the fox",
        "hello world hello world hello",
        "one",
        "",
        "   spaces   spaces   everywhere  spaces  "
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        char *deduped = remove_duplicate_words(tests[t]);
        if (deduped == NULL) {
            fprintf(stderr, "Error: memory allocation failed for test %zu\n", t);
            return EXIT_FAILURE;
        }
        printf("Input:  [%s]\n", tests[t]);
        printf("Output: [%s]\n\n", deduped);
        free(deduped);
    }

    return EXIT_SUCCESS;
}
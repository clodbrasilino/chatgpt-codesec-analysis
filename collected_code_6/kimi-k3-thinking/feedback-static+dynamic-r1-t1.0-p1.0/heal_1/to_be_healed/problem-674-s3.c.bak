#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        free(result);
        return NULL;
    }
    strcpy(copy, str);

    char **seen = NULL;
    size_t seen_count = 0;
    size_t out_len = 0;

    char *word = strtok(copy, " \t\n");
    while (word != NULL) {
        int found = 0;
        size_t i;
        for (i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], word) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            char **tmp = realloc(seen, (seen_count + 1) * sizeof(*seen));
            size_t wlen;

            if (tmp == NULL) {
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }
            seen = tmp;
            seen[seen_count] = word;
            seen_count++;

            wlen = strlen(word);
            if (out_len > 0) {
                result[out_len++] = ' ';
            }
            memcpy(result + out_len, word, wlen);
            out_len += wlen;
            result[out_len] = '\0';
        }

        word = strtok(NULL, " \t\n");
    }

    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    const char *input = "the quick brown fox jumps over the lazy dog the fox";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}
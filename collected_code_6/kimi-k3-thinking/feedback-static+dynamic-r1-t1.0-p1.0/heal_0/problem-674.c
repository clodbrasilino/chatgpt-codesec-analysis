#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    result[0] = '\0';

    size_t capacity = 16;
    size_t count = 0;
    char **words = malloc(capacity * sizeof(*words));
    if (words == NULL) {
        free(copy);
        free(result);
        return NULL;
    }

    size_t pos = 0;
    char *token = strtok(copy, " \t\n\r");
    while (token != NULL) {
        int found = 0;
        for (size_t i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (count == capacity) {
                size_t new_capacity = capacity * 2;
                char **tmp = realloc(words, new_capacity * sizeof(*words));
                if (tmp == NULL) {
                    free(words);
                    free(copy);
                    free(result);
                    return NULL;
                }
                words = tmp;
                capacity = new_capacity;
            }

            words[count++] = token;

            size_t word_len = strlen(token);
            if (pos > 0) {
                result[pos++] = ' ';
            }
            memcpy(result + pos, token, word_len);
            pos += word_len;
            result[pos] = '\0';
        }

        token = strtok(NULL, " \t\n\r");
    }

    free(words);
    free(copy);

    char *shrunk = realloc(result, pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

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
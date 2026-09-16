#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear(const char *const *strings, size_t count)
{
    char *result = NULL;
    size_t i;

    if (strings == NULL || count == 0U) {
        return NULL;
    }

    result = malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        len = strlen(strings[i]);
        if (len == 0U) {
            result[i] = ' ';
        } else {
            result[i] = strings[i][len - 1U];
        }
    }

    result[count] = '\0';
    return result;
}

static void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    char buffer[4096];
    char **words = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    char *rear = NULL;
    size_t i;
    int used_default = 0;
    const char *const default_words[] = { "Mers", "for", "Vers" };
    size_t default_count = sizeof(default_words) / sizeof(default_words[0]);

    while (scanf("%4095s", buffer) == 1) {
        if (count == capacity) {
            size_t new_capacity = (capacity == 0U) ? 8U : capacity * 2U;
            char **tmp = realloc(words, new_capacity * sizeof(char *));
            if (tmp == NULL) {
                free_words(words, count);
                (void)fprintf(stderr, "Extraction failed\n");
                return EXIT_FAILURE;
            }
            words = tmp;
            capacity = new_capacity;
        }
        words[count] = malloc(strlen(buffer) + 1U);
        if (words[count] == NULL) {
            free_words(words, count);
            (void)fprintf(stderr, "Extraction failed\n");
            return EXIT_FAILURE;
        }
        strcpy(words[count], buffer);
        count++;
    }

    if (count == 0U) {
        used_default = 1;
        rear = extract_rear(default_words, default_count);
        count = default_count;
    } else {
        rear = extract_rear((const char *const *)words, count);
    }

    if (rear == NULL) {
        if (used_default == 0) {
            free_words(words, count);
        }
        (void)fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    if (printf("[") < 0) {
        free(rear);
        if (used_default == 0) {
            free_words(words, count);
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'", rear[i]) < 0) {
            free(rear);
            if (used_default == 0) {
                free_words(words, count);
            }
            return EXIT_FAILURE;
        }
        if (i + 1U < count) {
            if (printf(", ") < 0) {
                free(rear);
                if (used_default == 0) {
                    free_words(words, count);
                }
                return EXIT_FAILURE;
            }
        }
    }

    if (printf("]\n") < 0) {
        free(rear);
        if (used_default == 0) {
            free_words(words, count);
        }
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(rear);
        if (used_default == 0) {
            free_words(words, count);
        }
        return EXIT_FAILURE;
    }

    free(rear);
    if (used_default == 0) {
        free_words(words, count);
    }
    return EXIT_SUCCESS;
}
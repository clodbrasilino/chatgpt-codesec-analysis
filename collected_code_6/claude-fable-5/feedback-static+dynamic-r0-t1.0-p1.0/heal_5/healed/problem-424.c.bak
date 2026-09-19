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

static char **read_words_from_line(size_t *out_count)
{
    char **words = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    char line[8192];
    char *token;
    const char *delims = " \t\r\n[],'\"";

    *out_count = 0U;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return NULL;
    }

    token = strtok(line, delims);
    while (token != NULL) {
        char *copy;

        if (count == capacity) {
            size_t new_capacity = (capacity == 0U) ? 8U : capacity * 2U;
            char **tmp = realloc(words, new_capacity * sizeof(char *));
            if (tmp == NULL) {
                free_words(words, count);
                return NULL;
            }
            words = tmp;
            capacity = new_capacity;
        }

        copy = malloc(strlen(token) + 1U);
        if (copy == NULL) {
            free_words(words, count);
            return NULL;
        }
        strcpy(copy, token);
        words[count] = copy;
        count++;

        token = strtok(NULL, delims);
    }

    *out_count = count;
    return words;
}

static int print_result(const char *rear, size_t count)
{
    size_t i;

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'", rear[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    const char *const default_words[] = { "Mers", "for", "Vers" };
    size_t default_count = sizeof(default_words) / sizeof(default_words[0]);
    const char *const *strings = NULL;
    size_t count = 0U;
    char **stdin_words = NULL;
    size_t stdin_count = 0U;
    char *rear = NULL;
    int status;

    if (argc > 1) {
        strings = (const char *const *)&argv[1];
        count = (size_t)(argc - 1);
    } else {
        stdin_words = read_words_from_line(&stdin_count);
        if (stdin_words != NULL && stdin_count > 0U) {
            strings = (const char *const *)stdin_words;
            count = stdin_count;
        } else {
            free_words(stdin_words, stdin_count);
            stdin_words = NULL;
            stdin_count = 0U;
            strings = default_words;
            count = default_count;
        }
    }

    rear = extract_rear(strings, count);
    if (rear == NULL) {
        (void)fprintf(stderr, "Extraction failed\n");
        free_words(stdin_words, stdin_count);
        return EXIT_FAILURE;
    }

    status = print_result(rear, count);

    free(rear);
    free_words(stdin_words, stdin_count);

    if (status != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
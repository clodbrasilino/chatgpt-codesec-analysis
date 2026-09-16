#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char **tokenize(char *line, size_t *out_count)
{
    char **words = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    char *token;
    const char *delims = " \t\r\n[],'\"";

    *out_count = 0U;

    if (line == NULL) {
        return NULL;
    }

    token = strtok(line, delims);
    while (token != NULL) {
        char *copy;
        size_t token_len;

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

        token_len = strlen(token);
        copy = malloc(token_len + 1U);
        if (copy == NULL) {
            free_words(words, count);
            return NULL;
        }
        memcpy(copy, token, token_len + 1U);
        words[count] = copy;
        count++;

        token = strtok(NULL, delims);
    }

    *out_count = count;
    return words;
}

static char **read_words_from_stdin(size_t *out_count)
{
    char *buffer = NULL;
    size_t used = 0U;
    size_t capacity = 0U;
    char chunk[4096];
    char **words = NULL;

    *out_count = 0U;

    while (fgets(chunk, (int)sizeof(chunk), stdin) != NULL) {
        size_t len = strlen(chunk);

        if (used + len + 1U > capacity) {
            size_t new_capacity = (capacity == 0U) ? 8192U : capacity * 2U;
            char *tmp;

            while (new_capacity < used + len + 1U) {
                new_capacity *= 2U;
            }
            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        memcpy(&buffer[used], chunk, len + 1U);
        used += len;
    }

    if (buffer == NULL) {
        return NULL;
    }

    words = tokenize(buffer, out_count);
    free(buffer);
    return words;
}

static char **read_words_from_args(int argc, char **argv, size_t *out_count)
{
    char buffer[8192];
    size_t used = 0U;
    int i;

    *out_count = 0U;
    buffer[0] = '\0';

    for (i = 1; i < argc; i++) {
        size_t len = strlen(argv[i]);

        if (used + len + 2U >= sizeof(buffer)) {
            break;
        }
        if (used > 0U) {
            buffer[used] = ' ';
            used++;
            buffer[used] = '\0';
        }
        memcpy(&buffer[used], argv[i], len + 1U);
        used += len;
    }

    return tokenize(buffer, out_count);
}

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

static int print_result(const char *rear, size_t count)
{
    size_t i;

    if (rear == NULL) {
        return -1;
    }

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
    char **parsed_words = NULL;
    size_t parsed_count = 0U;
    char *rear = NULL;
    int status;

    if (argc > 1) {
        parsed_words = read_words_from_args(argc, argv, &parsed_count);
    } else {
        parsed_words = read_words_from_stdin(&parsed_count);
    }

    if (parsed_words != NULL && parsed_count > 0U) {
        strings = (const char *const *)parsed_words;
        count = parsed_count;
    } else {
        free_words(parsed_words, parsed_count);
        parsed_words = NULL;
        parsed_count = 0U;
        strings = default_words;
        count = default_count;
    }

    rear = extract_rear(strings, count);
    if (rear == NULL) {
        (void)fprintf(stderr, "Extraction failed\n");
        free_words(parsed_words, parsed_count);
        return EXIT_FAILURE;
    }

    status = print_result(rear, count);

    free(rear);
    free_words(parsed_words, parsed_count);

    if (status != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
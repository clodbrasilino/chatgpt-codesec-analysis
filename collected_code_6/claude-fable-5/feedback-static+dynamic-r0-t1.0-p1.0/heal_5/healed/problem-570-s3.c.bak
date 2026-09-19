#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src) + 1U;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    return copy;
}

static void free_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static char *read_line(FILE *fp)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    ch = fgetc(fp);
    if (ch == EOF) {
        free(buffer);
        return NULL;
    }

    while (ch != EOF && ch != '\n') {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity * 2U;
            char *tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length] = (char)ch;
        length++;
        ch = fgetc(fp);
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        length--;
    }

    buffer[length] = '\0';
    return buffer;
}

static char **remove_words(const char *const *words, size_t count,
                           const char *pattern, size_t *out_count)
{
    char **result;
    size_t kept;
    size_t i;
    size_t alloc_count;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || pattern == NULL) {
        return NULL;
    }

    alloc_count = (count == 0U) ? 1U : count;
    result = malloc(alloc_count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strcmp(words[i], pattern) != 0) {
            result[kept] = duplicate_string(words[i]);
            if (result[kept] == NULL) {
                free_word_list(result, kept);
                return NULL;
            }
            kept++;
        }
    }

    if (kept > 0U && kept < count) {
        char **shrunk = realloc(result, kept * sizeof(*shrunk));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *out_count = kept;
    return result;
}

static int print_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL && count > 0U) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (printf("'%s'", list[i]) < 0) {
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

int main(void)
{
    char *count_line;
    char *pattern;
    char **words;
    char **filtered;
    size_t count;
    size_t filtered_count;
    size_t i;
    unsigned long parsed;
    char *endptr;

    count_line = read_line(stdin);
    if (count_line == NULL) {
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }

    parsed = strtoul(count_line, &endptr, 10);
    if (endptr == count_line) {
        free(count_line);
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }
    free(count_line);

    count = (size_t)parsed;

    words = malloc((count == 0U ? 1U : count) * sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        words[i] = read_line(stdin);
        if (words[i] == NULL) {
            free_word_list(words, i);
            fprintf(stderr, "An error occurred.\n");
            return EXIT_FAILURE;
        }
    }

    pattern = read_line(stdin);
    if (pattern == NULL) {
        free_word_list(words, count);
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }

    filtered = remove_words((const char *const *)words, count, pattern,
                            &filtered_count);

    free_word_list(words, count);
    free(pattern);

    if (filtered == NULL && filtered_count > 0U) {
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }

    if (filtered == NULL) {
        if (printf("[]\n") < 0) {
            return EXIT_FAILURE;
        }
        if (fflush(stdout) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_word_list(filtered, filtered_count) < 0) {
        free_word_list(filtered, filtered_count);
        return EXIT_FAILURE;
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}
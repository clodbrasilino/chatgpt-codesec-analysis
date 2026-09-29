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
    size_t capacity = 64;
    size_t length = 0;
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
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
        ch = fgetc(fp);
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        length--;
    }
    buffer[length] = '\0';
    return buffer;
}

static char **read_all_lines(FILE *fp, size_t *out_count)
{
    size_t capacity = 16;
    size_t count = 0;
    char **lines;
    char *line;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    lines = malloc(capacity * sizeof(*lines));
    if (lines == NULL) {
        return NULL;
    }

    while ((line = read_line(fp)) != NULL) {
        if (count >= capacity) {
            size_t new_capacity = capacity * 2;
            char **tmp = realloc(lines, new_capacity * sizeof(*tmp));
            if (tmp == NULL) {
                free(line);
                free_word_list(lines, count);
                return NULL;
            }
            lines = tmp;
            capacity = new_capacity;
        }
        lines[count++] = line;
    }

    if (count == 0) {
        free(lines);
        return NULL;
    }

    *out_count = count;
    return lines;
}

static char **remove_words(const char *const *words, size_t count,
                           const char *pattern, size_t *out_count)
{
    char **result;
    size_t kept;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || pattern == NULL || count == 0U) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
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

    if (kept == 0U) {
        free(result);
        return NULL;
    }

    if (kept < count) {
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

    if (printf("[") < 0) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (printf("'%s'%s", list[i],
                   (i + 1 < count) ? ", " : "") < 0) {
            return -1;
        }
    }
    if (printf("]\n") < 0) {
        return -1;
    }
    if (fflush(stdout) == EOF) {
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    static const char *const default_words[] = {
        "Red", "", "Green", "Black", "Orange", "White", "Black"
    };
    static const char *const default_pattern = "Black";
    const char *const *words;
    const char *pattern;
    size_t count;
    char **filtered;
    char **input_lines = NULL;
    size_t line_count = 0;
    size_t filtered_count = 0;
    int status = EXIT_SUCCESS;

    if (argc >= 3) {
        words = (const char *const *)&argv[1];
        count = (size_t)(argc - 2);
        pattern = argv[argc - 1];
    } else {
        input_lines = read_all_lines(stdin, &line_count);
        if (input_lines != NULL && line_count >= 2) {
            words = (const char *const *)input_lines;
            count = line_count - 1;
            pattern = input_lines[line_count - 1];
        } else {
            if (input_lines != NULL) {
                free_word_list(input_lines, line_count);
                input_lines = NULL;
                line_count = 0;
            }
            words = default_words;
            count = sizeof(default_words) / sizeof(default_words[0]);
            pattern = default_pattern;
        }
    }

    filtered = remove_words(words, count, pattern, &filtered_count);
    if (filtered == NULL) {
        if (printf("[]\n") < 0 || fflush(stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    } else {
        if (print_word_list(filtered, filtered_count) != 0) {
            status = EXIT_FAILURE;
        }
        free_word_list(filtered, filtered_count);
    }

    if (input_lines != NULL) {
        free_word_list(input_lines, line_count);
    }

    return status;
}
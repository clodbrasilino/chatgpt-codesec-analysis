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
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch;

    if (fp == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
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
    }

    if (length == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static char **split_words(const char *line, size_t *out_count)
{
    char **list = NULL;
    size_t count = 0;
    size_t capacity = 0;
    char *work;
    char *token;

    if (line == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    work = duplicate_string(line);
    if (work == NULL) {
        return NULL;
    }

    token = strtok(work, " \t");
    while (token != NULL) {
        if (count >= capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            char **tmp = realloc(list, new_capacity * sizeof(char *));
            if (tmp == NULL) {
                free_word_list(list, count);
                free(work);
                return NULL;
            }
            list = tmp;
            capacity = new_capacity;
        }

        list[count] = duplicate_string(token);
        if (list[count] == NULL) {
            free_word_list(list, count);
            free(work);
            return NULL;
        }
        count++;

        token = strtok(NULL, " \t");
    }

    free(work);
    *out_count = count;
    return list;
}

int main(void)
{
    char *line;

    while ((line = read_line(stdin)) != NULL) {
        size_t count = 0;
        char **words = split_words(line, &count);

        if (words != NULL) {
            for (size_t i = 0; i < count; i++) {
                printf("word[%zu]: %s\n", i, words[i]);
            }
            free_word_list(words, count);
        }

        free(line);
    }

    return EXIT_SUCCESS;
}
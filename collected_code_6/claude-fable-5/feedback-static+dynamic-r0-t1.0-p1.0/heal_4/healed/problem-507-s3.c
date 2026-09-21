#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t kept;
    int match;

    if (words == NULL || new_count == NULL) {
        return NULL;
    }

    result = calloc(count > 0 ? count : 1, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        match = 0;
        for (j = 0; j < target_count; j++) {
            if (targets != NULL && targets[j] != NULL &&
                strcmp(words[i], targets[j]) == 0) {
                match = 1;
                break;
            }
        }
        if (match == 0) {
            size_t len = strlen(words[i]);
            result[kept] = malloc(len + 1);
            if (result[kept] == NULL) {
                while (kept > 0) {
                    kept--;
                    free(result[kept]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[kept], words[i], len);
            result[kept][len] = '\0';
            kept++;
        }
    }

    *new_count = kept;
    return result;
}

void free_word_list(char **list, size_t count)
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

static char **split_line(char *line, size_t *count)
{
    char **tokens;
    char *tok;
    char *saveptr;
    size_t capacity;
    size_t n;
    char **tmp;

    if (line == NULL || count == NULL) {
        return NULL;
    }

    capacity = 8;
    n = 0;
    tokens = malloc(sizeof(char *) * capacity);
    if (tokens == NULL) {
        return NULL;
    }

    saveptr = NULL;
    tok = strtok_r(line, " \t\r\n", &saveptr);
    while (tok != NULL) {
        if (n >= capacity) {
            if (capacity > ((size_t)-1) / (2 * sizeof(char *))) {
                free(tokens);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(tokens, sizeof(char *) * capacity);
            if (tmp == NULL) {
                free(tokens);
                return NULL;
            }
            tokens = tmp;
        }
        tokens[n] = tok;
        n++;
        tok = strtok_r(NULL, " \t\r\n", &saveptr);
    }

    *count = n;
    return tokens;
}

static void print_list(char **list, size_t count)
{
    size_t i;

    printf("[");
    for (i = 0; i < count; i++) {
        printf("'%s'", list[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    char word_line[4096];
    char target_line[4096];
    char **words;
    char **targets;
    char **filtered;
    size_t word_count;
    size_t target_count;
    size_t new_count;

    word_count = 0;
    target_count = 0;
    new_count = 0;

    memset(word_line, 0, sizeof(word_line));
    memset(target_line, 0, sizeof(target_line));

    if (fgets(word_line, (int)sizeof(word_line), stdin) == NULL) {
        fprintf(stderr, "Failed to read words\n");
        return EXIT_FAILURE;
    }
    word_line[sizeof(word_line) - 1] = '\0';

    if (fgets(target_line, (int)sizeof(target_line), stdin) == NULL) {
        target_line[0] = '\0';
    }
    target_line[sizeof(target_line) - 1] = '\0';

    words = split_line(word_line, &word_count);
    if (words == NULL) {
        fprintf(stderr, "Failed to parse words\n");
        return EXIT_FAILURE;
    }

    targets = split_line(target_line, &target_count);
    if (targets == NULL) {
        free(words);
        fprintf(stderr, "Failed to parse targets\n");
        return EXIT_FAILURE;
    }

    filtered = remove_words(words, word_count, targets, target_count, &new_count);
    if (filtered == NULL) {
        free(words);
        free(targets);
        fprintf(stderr, "Failed to remove words\n");
        return EXIT_FAILURE;
    }

    print_list(filtered, new_count);
    fflush(stdout);

    free_word_list(filtered, new_count);
    free(words);
    free(targets);
    return EXIT_SUCCESS;
}
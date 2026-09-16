#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count);
void free_word_list(char **list, size_t count);
static size_t tokenize(char *line, char **tokens, size_t max_tokens);
static int is_delim(char c);

static int is_delim(char c)
{
    const char *delims = " \t\r\n[](){},'\"";
    size_t i;

    for (i = 0; delims[i] != '\0'; i++) {
        if (c == delims[i]) {
            return 1;
        }
    }
    return 0;
}

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t kept;
    int match;

    if (new_count == NULL) {
        return NULL;
    }

    *new_count = 0;

    if (words == NULL && count > 0) {
        return NULL;
    }

    result = malloc(sizeof(char *) * (count > 0 ? count : 1));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        match = 0;
        if (targets != NULL) {
            for (j = 0; j < target_count; j++) {
                if (targets[j] != NULL && strcmp(words[i], targets[j]) == 0) {
                    match = 1;
                    break;
                }
            }
        }
        if (match == 0) {
            size_t len = strlen(words[i]) + 1;
            result[kept] = malloc(len);
            if (result[kept] == NULL) {
                while (kept > 0) {
                    kept--;
                    free(result[kept]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[kept], words[i], len);
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

static size_t tokenize(char *line, char **tokens, size_t max_tokens)
{
    size_t count = 0;
    size_t i = 0;

    if (line == NULL || tokens == NULL) {
        return 0;
    }

    while (line[i] != '\0' && count < max_tokens) {
        while (line[i] != '\0' && is_delim(line[i])) {
            i++;
        }
        if (line[i] == '\0') {
            break;
        }
        tokens[count] = &line[i];
        count++;
        while (line[i] != '\0' && !is_delim(line[i])) {
            i++;
        }
        if (line[i] != '\0') {
            line[i] = '\0';
            i++;
        }
    }
    return count;
}

int main(void)
{
    static char words_line[8192];
    static char targets_line[8192];
    static char *words[1024];
    static char *targets[1024];
    size_t word_count;
    size_t target_count;
    size_t new_count = 0;
    size_t i;
    char **filtered;

    words_line[0] = '\0';
    targets_line[0] = '\0';

    if (fgets(words_line, sizeof(words_line), stdin) == NULL) {
        words_line[0] = '\0';
    }
    if (fgets(targets_line, sizeof(targets_line), stdin) == NULL) {
        targets_line[0] = '\0';
    }

    word_count = tokenize(words_line, words, 1024);
    target_count = tokenize(targets_line, targets, 1024);

    filtered = remove_words(words, word_count, targets, target_count, &new_count);
    if (filtered == NULL) {
        printf("[]\n");
        fflush(stdout);
        return EXIT_SUCCESS;
    }

    printf("[");
    for (i = 0; i < new_count; i++) {
        printf("'%s'", filtered[i]);
        if (i + 1 < new_count) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);

    free_word_list(filtered, new_count);
    return EXIT_SUCCESS;
}
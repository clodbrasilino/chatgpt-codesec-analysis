#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

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
        for (j = 0; j < target_count; j++) {
            if (targets != NULL && targets[j] != NULL &&
                strcmp(words[i], targets[j]) == 0) {
                match = 1;
                break;
            }
        }
        if (match == 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
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
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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

static char **split_line(char *line, size_t *count)
{
    char **tokens;
    char *tok;
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

    tok = strtok(line, " \t\r\n");
    while (tok != NULL) {
        if (n >= capacity) {
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
        tok = strtok(NULL, " \t\r\n");
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word_line[4096];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    if (fgets(word_line, sizeof(word_line), stdin) == NULL) {
        fprintf(stderr, "Failed to read words\n");
        return EXIT_FAILURE;
    }
    word_line[sizeof(word_line) - 1] = '\0';

    if (fgets(target_line, sizeof(target_line), stdin) == NULL) {
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
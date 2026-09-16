#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
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

static char **split_line(char *line, size_t *count_out)
{
    char **tokens;
    size_t capacity;
    size_t count;
    char *token;

    capacity = 8;
    count = 0;
    tokens = malloc(sizeof(char *) * capacity);
    if (tokens == NULL) {
        return NULL;
    }

    token = strtok(line, " \t\r\n,'[]");
    while (token != NULL) {
        if (count >= capacity) {
            char **tmp;
            capacity *= 2;
            tmp = realloc(tokens, sizeof(char *) * capacity);
            if (tmp == NULL) {
                free(tokens);
                return NULL;
            }
            tokens = tmp;
        }
        tokens[count] = token;
        count++;
        token = strtok(NULL, " \t\r\n,'[]");
    }

    *count_out = count;
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
    char words_line[4096];
    char targets_line[4096];
    char **words;
    char **targets;
    size_t word_count;
    size_t target_count;
    size_t new_count;
    char **filtered;

    if (fgets(words_line, sizeof(words_line), stdin) == NULL) {
        fprintf(stderr, "Failed to read words\n");
        return EXIT_FAILURE;
    }
    if (fgets(targets_line, sizeof(targets_line), stdin) == NULL) {
        targets_line[0] = '\0';
    }

    word_count = 0;
    target_count = 0;
    new_count = 0;

    words = split_line(words_line, &word_count);
    if (words == NULL) {
        fprintf(stderr, "Failed to parse words\n");
        return EXIT_FAILURE;
    }

    targets = split_line(targets_line, &target_count);
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

    free_word_list(filtered, new_count);
    free(words);
    free(targets);
    return EXIT_SUCCESS;
}
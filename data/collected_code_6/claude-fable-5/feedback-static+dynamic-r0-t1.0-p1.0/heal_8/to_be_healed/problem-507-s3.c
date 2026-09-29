#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count);
void free_word_list(char **list, size_t count);
static char **split_line(char *line, size_t *count);
static void print_list(char **list, size_t count);
static char *read_line(FILE *fp);
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

    if (count > ((size_t)-1) / sizeof(char *)) {
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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
            if (len == (size_t)-1) {
                free_word_list(result, kept);
                return NULL;
            }
            result[kept] = malloc(len + 1);
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

static char *read_line(FILE *fp)
{
    char *buf;
    size_t capacity;
    size_t length;
    int c;
    char *tmp;

    capacity = 128;
    length = 0;
    buf = malloc(capacity);
    if (buf == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = fgetc(fp);
    if (c == EOF) {
        free(buf);
        return NULL;
    }

    while (c != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > ((size_t)-1) / 2) {
                free(buf);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(buf, capacity);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[length] = (char)c;
        length++;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(fp);
    }

    buf[length] = '\0';
    return buf;
}

static char **split_line(char *line, size_t *count)
{
    char **tokens;
    char *tok;
    char *saveptr;
    size_t capacity;
    size_t n;
    char **tmp;
    const char *delims = " \t\r\n,[]'\"";

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
    tok = strtok_r(line, delims, &saveptr);
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
        tok = strtok_r(NULL, delims, &saveptr);
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
    char *word_line;
    char *target_line;
    char **words;
    char **targets;
    char **filtered;
    size_t word_count;
    size_t target_count;
    size_t new_count;

    word_count = 0;
    target_count = 0;
    new_count = 0;

    word_line = read_line(stdin);
    if (word_line == NULL) {
        fprintf(stderr, "Failed to read words\n");
        return EXIT_FAILURE;
    }

    target_line = read_line(stdin);
    if (target_line == NULL) {
        target_line = malloc(1);
        if (target_line == NULL) {
            free(word_line);
            fprintf(stderr, "Out of memory\n");
            return EXIT_FAILURE;
        }
        target_line[0] = '\0';
    }

    words = split_line(word_line, &word_count);
    if (words == NULL) {
        free(word_line);
        free(target_line);
        fprintf(stderr, "Failed to parse words\n");
        return EXIT_FAILURE;
    }

    targets = split_line(target_line, &target_count);
    if (targets == NULL) {
        free(words);
        free(word_line);
        free(target_line);
        fprintf(stderr, "Failed to parse targets\n");
        return EXIT_FAILURE;
    }

    filtered = remove_words(words, word_count, targets, target_count, &new_count);
    if (filtered == NULL) {
        free(words);
        free(targets);
        free(word_line);
        free(target_line);
        fprintf(stderr, "Failed to remove words\n");
        return EXIT_FAILURE;
    }

    print_list(filtered, new_count);
    fflush(stdout);

    free_word_list(filtered, new_count);
    free(words);
    free(targets);
    free(word_line);
    free(target_line);
    return EXIT_SUCCESS;
}
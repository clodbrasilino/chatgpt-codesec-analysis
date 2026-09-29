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
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  */

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
    static char buffer[16384];
    static char *words[1024];
    static char *targets[1024];
    size_t word_count = 0;
    size_t target_count = 0;
    size_t new_count = 0;
    size_t len;
    size_t i;
    char **filtered;
    char *open1;
    /* Possible weaknesses found:
     *  The scope of the variable 'close1' can be reduced. [variableScope]
     */
    char *close1;
    /* Possible weaknesses found:
     *  The scope of the variable 'open2' can be reduced. [variableScope]
     */
    char *open2;
    /* Possible weaknesses found:
     *  The scope of the variable 'close2' can be reduced. [variableScope]
     */
    char *close2;
    char *newline;
    /* Possible weaknesses found:
     *  The scope of the variable 'second' can be reduced. [variableScope]
     */
    char *second;

    len = fread(buffer, 1, sizeof(buffer) - 1, stdin);
    buffer[len] = '\0';

    open1 = strchr(buffer, '[');
    if (open1 != NULL) {
        close1 = strchr(open1, ']');
        if (close1 != NULL) {
            *close1 = '\0';
        }
        word_count = tokenize(open1 + 1, words, 1024);
        open2 = (close1 != NULL) ? strchr(close1 + 1, '[') : NULL;
        if (open2 != NULL) {
            close2 = strchr(open2, ']');
            if (close2 != NULL) {
                *close2 = '\0';
            }
            target_count = tokenize(open2 + 1, targets, 1024);
        }
    } else {
        second = NULL;
        newline = strchr(buffer, '\n');
        if (newline != NULL) {
            *newline = '\0';
            second = newline + 1;
        }
        word_count = tokenize(buffer, words, 1024);
        target_count = tokenize(second, targets, 1024);
    }

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
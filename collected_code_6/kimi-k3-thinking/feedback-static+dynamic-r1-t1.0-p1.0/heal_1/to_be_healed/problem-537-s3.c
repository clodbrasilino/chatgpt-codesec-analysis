#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_delimiter(char c)
{
    return isspace((unsigned char)c) || ispunct((unsigned char)c);
}

static char *copy_word(const char *start, size_t len)
{
    char *word = malloc(len + 1);
    if (word == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(word, start, len);
    word[len] = '\0';
    return word;
}

static void free_words(char **words, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  */

char *find_first_repeated_word(const char *str)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t capacity, count, i, len;
    char **seen, **resized, *result;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    const char *p, *start;

    if (str == NULL || *str == '\0') {
        return NULL;
    }

    capacity = 16;
    count = 0;
    seen = malloc(capacity * sizeof(*seen));
    if (seen == NULL) {
        return NULL;
    }

    p = str;
    while (*p != '\0') {
        while (*p != '\0' && is_delimiter(*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        start = p;
        while (*p != '\0' && !is_delimiter(*p)) {
            p++;
        }
        len = (size_t)(p - start);

        for (i = 0; i < count; i++) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(seen[i]) == len && strncmp(seen[i], start, len) == 0) {
                result = copy_word(start, len);
                free_words(seen, count);
                return result;
            }
        }

        if (count == capacity) {
            resized = realloc(seen, capacity * 2 * sizeof(*resized));
            if (resized == NULL) {
                free_words(seen, count);
                return NULL;
            }
            seen = resized;
            capacity *= 2;
        }

        seen[count] = copy_word(start, len);
        if (seen[count] == NULL) {
            free_words(seen, count);
            return NULL;
        }
        count++;
    }

    free_words(seen, count);
    return NULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *word;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    word = find_first_repeated_word(input);
    if (word != NULL) {
        printf("First repeated word: %s\n", word);
        free(word);
    } else {
        printf("No repeated word found.\n");
    }

    return EXIT_SUCCESS;
}
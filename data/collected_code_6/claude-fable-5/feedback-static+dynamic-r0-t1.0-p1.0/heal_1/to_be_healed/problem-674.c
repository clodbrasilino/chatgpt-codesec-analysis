#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *input);
static int word_seen(char **words, size_t count, const char *word);
static void free_words(char **words, size_t count);

static int word_seen(char **words, size_t count, const char *word)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static void free_words(char **words, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

char *remove_duplicate_words(const char *input)
{
    char *copy;
    char *result;
    char **words;
    char *token;
    char *saveptr;
    size_t count;
    size_t capacity;
    size_t len;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, len + 1);

    capacity = 16;
    count = 0;
    words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(copy);
        return NULL;
    }

    token = strtok_r(copy, " \t\n", &saveptr);
    while (token != NULL) {
        if (!word_seen(words, count, token)) {
            if (count == capacity) {
                size_t new_capacity = capacity * 2;
                char **tmp = realloc(words, new_capacity * sizeof(char *));
                if (tmp == NULL) {
                    free_words(words, count);
                    free(copy);
                    return NULL;
                }
                words = tmp;
                capacity = new_capacity;
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            words[count] = malloc(strlen(token) + 1);
            if (words[count] == NULL) {
                free_words(words, count);
                free(copy);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(words[count], token);
            count++;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free(copy);

    result = malloc(len + 1);
    if (result == NULL) {
        free_words(words, count);
        return NULL;
    }

    result[0] = '\0';
    for (i = 0; i < count; i++) {
        if (i > 0) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, words[i]);
    }

    free_words(words, count);
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox the lazy dog quick brown";
    char *deduped;

    deduped = remove_duplicate_words(text);
    if (deduped == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", text);
    printf("Deduplicated: %s\n", deduped);

    free(deduped);
    return EXIT_SUCCESS;
}
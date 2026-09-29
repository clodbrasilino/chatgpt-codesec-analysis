#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words(const char *input, size_t *count)
{
    char *copy;
    char **results;
    char **temp;
    char *token;
    size_t capacity;
    size_t n;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    capacity = 8;
    n = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    copy = malloc(strlen(input) + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, input);

    results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        free(copy);
        return NULL;
    }

    token = strtok(copy, " \t\n\r.,;:!?");
    while (token != NULL) {
        char first = (char)tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if (n == capacity) {
                capacity *= 2;
                temp = realloc(results, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (size_t i = 0; i < n; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    return NULL;
                }
                results = temp;
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            results[n] = malloc(strlen(token) + 1);
            if (results[n] == NULL) {
                for (size_t i = 0; i < n; i++) {
                    free(results[i]);
                }
                free(results);
                free(copy);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(results[n], token);
            n++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    free(copy);
    *count = n;
    return results;
}

void free_words(char **words, size_t count)
{
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    const char *text = "An apple and an egg are on every table each evening";
    size_t count = 0;
    char **words = find_words(text, &count);

    if (words == NULL) {
        fprintf(stderr, "Failed to process input\n");
        return EXIT_FAILURE;
    }

    printf("Words starting with 'a' or 'e':\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}
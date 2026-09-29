#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words(const char *input, size_t *count)
{
    char *copy = NULL;
    char **results = NULL;
    char **temp = NULL;
    char *token = NULL;
    size_t capacity = 8;
    size_t i;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

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
            if (*count == capacity) {
                capacity *= 2;
                temp = realloc(results, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (i = 0; i < *count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                results = temp;
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            results[*count] = malloc(strlen(token) + 1);
            if (results[*count] == NULL) {
                for (i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                free(copy);
                *count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(results[*count], token);
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    free(copy);
    return results;
}

void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    const char *text = "An apple and an egg were eaten by everyone at the event.";
    char **words = NULL;
    size_t count = 0;
    size_t i;

    words = find_words(text, &count);
    if (words == NULL && count == 0) {
        if (printf("No matching words found or an error occurred.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words starting with 'a' or 'e':\n") < 0) {
        free_words(words, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", words[i]) < 0) {
            free_words(words, count);
            return EXIT_FAILURE;
        }
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}
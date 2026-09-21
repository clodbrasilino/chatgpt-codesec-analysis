#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_most_frequent_word(const char *const words[], size_t count)
{
    size_t i, j;
    size_t max_count = 0;
    size_t max_index = 0;
    int found = 0;
    char *result;

    if (words == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t current_count = 0;

        if (words[i] == NULL) {
            continue;
        }

        for (j = 0; j < count; j++) {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0) {
                current_count++;
            }
        }

        if (!found || current_count > max_count) {
            max_count = current_count;
            max_index = i;
            found = 1;
        }
    }

    if (!found) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = malloc(strlen(words[max_index]) + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, words[max_index]);

    return result;
}

int main(void)
{
    const char *words[] = {
        "apple", "banana", "apple", "cherry",
        "banana", "apple", "cherry", "banana"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    char *most_frequent;

    most_frequent = find_most_frequent_word(words, count);
    if (most_frequent == NULL) {
        fprintf(stderr, "Error: unable to determine the most frequent word\n");
        return EXIT_FAILURE;
    }

    printf("Most frequent word: %s\n", most_frequent);

    free(most_frequent);

    return EXIT_SUCCESS;
}
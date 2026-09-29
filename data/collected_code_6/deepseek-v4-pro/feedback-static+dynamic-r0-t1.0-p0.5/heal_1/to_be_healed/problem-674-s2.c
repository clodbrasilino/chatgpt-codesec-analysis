#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    collection->count = 0;
}

int contains_word(WordCollection *collection, const char *word) {
    for (int i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_word(WordCollection *collection, const char *word) {
    if (collection->count < MAX_WORDS && !contains_word(collection, word)) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(collection->words[collection->count], word, MAX_WORD_LEN - 1);
        collection->words[collection->count][MAX_WORD_LEN - 1] = '\0';
        collection->count++;
    }
}

void remove_duplicate_words(char *str) {
    if (str == NULL) {
        return;
    }

    WordCollection collection;
    init_collection(&collection);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = (char *)malloc(strlen(str) + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *token;
    char *rest = str;
    char *delimiters = " \t\n\r\f\v";

    while ((token = strtok_r(rest, delimiters, &rest)) != NULL) {
        if (!contains_word(&collection, token)) {
            add_word(&collection, token);
            if (result[0] != '\0') {
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcat(result, " ");
            }
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, token);
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
    free(result);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1000];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    remove_duplicate_words(str);

    printf("String after removing duplicates: %s\n", str);

    return 0;
}
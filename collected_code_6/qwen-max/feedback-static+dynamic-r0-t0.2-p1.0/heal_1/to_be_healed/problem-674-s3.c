#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

char *remove_duplicates(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;
    const char *token;
    char *output = NULL;
    char *new_word;
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    int i, j, found;

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        found = 0;
        for (i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            new_word = strdup(token);
            if (new_word == NULL) {
                for (i = 0; i < word_count; ++i) {
                    free(words[i]);
                }
                return NULL;
            }
            words[word_count++] = new_word;
        }
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    output = (char *)malloc(strlen(input) + 1);
    if (output == NULL) {
        for (i = 0; i < word_count; ++i) {
            free(words[i]);
        }
        return NULL;
    }
    output[0] = '\0';

    for (i = 0; i < word_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(output, words[i]);
        if (i < word_count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(output, " ");
        }
        free(words[i]);
    }

    return output;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *result = remove_duplicates(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int count;
} WordSet;

void init_word_set(WordSet *set) {
    set->count = 0;
}

bool add_word(WordSet *set, const char *word) {
    if (set->count >= MAX_WORDS) return false;
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->words[i], word) == 0) return true;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(set->words[set->count], word, MAX_WORD_LENGTH - 1);
    set->words[set->count][MAX_WORD_LENGTH - 1] = '\0';
    set->count++;
    return true;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    WordSet set;
    init_word_set(&set);
    char *token, *output = NULL, *temp = strdup(input), *result = NULL;
    token = strtok(temp, " ");
    while (token != NULL) {
        if (add_word(&set, token)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            int len = strlen(token) + 1;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             *  Common realloc mistake: 'output' nulled but not freed upon failure [memleakOnRealloc]
             */
            output = realloc(output, (strlen(output) + len) * sizeof(char));
            if (output == NULL) {
                free(temp);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(output, token);
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(output, " ");
        }
        token = strtok(NULL, " ");
    }
    if (output) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        output[strlen(output) - 1] = '\0'; // Remove trailing space
        result = strdup(output);
        free(output);
    }
    free(temp);
    return result;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Allocation failed.\n");
    }
    return 0;
}
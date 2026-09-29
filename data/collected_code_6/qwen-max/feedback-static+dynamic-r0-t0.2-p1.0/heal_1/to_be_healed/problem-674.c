#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as const array [constParameter]
 */
int is_word_in_array(char *word, char *array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array((char *)token, words, word_count)) {
            words[word_count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = (char *)malloc(strlen(input) + 1);
    result[0] = '\0';

    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, words[i]);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(result, " ");
        free(words[i]);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(result) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    printf("%s\n", output);
    free(output);
    return 0;
}
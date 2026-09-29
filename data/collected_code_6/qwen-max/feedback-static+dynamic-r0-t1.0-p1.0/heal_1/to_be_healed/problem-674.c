#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

/* Possible weaknesses found:
 *  expected 'const char **' but argument is of type 'char **'
 */
int is_word_in_array(const char *word, const char *words[], int num_words) {
    for (int i = 0; i < num_words; ++i) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got ython Exercises Practice Solution Exercises
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got ython Exercises Practice Solution Python
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got ython Exercises Practice Solution Practice
  */

char *remove_duplicate_words(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = (char *)malloc(strlen(input) + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS];
    int num_words = 0;

    const char *p = input;
    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) p++;
        const char *word_start = p;
        while (*p && isalnum((unsigned char)*p)) p++;

        /* Possible weaknesses found:
         *  passing argument 2 of 'is_word_in_array' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        if (word_start != p && !is_word_in_array(word_start, words, num_words)) {
            if (num_words >= MAX_WORDS) {
                free(result);
                return NULL;
            }
            words[num_words++] = word_start;
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result, word_start, p - word_start);
            result += p - word_start;
            *(result++) = ' ';
        }

        while (*p && !isalnum((unsigned char)*p)) p++;
    }
    *--result = '\0';

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return result - (strlen(input) - 1);
}

int main() {
    const char *input = "this this is a test test of a duplicate remover";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or too many unique words.\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Processed: %s\n", output);

    free(output);
    return 0;
}
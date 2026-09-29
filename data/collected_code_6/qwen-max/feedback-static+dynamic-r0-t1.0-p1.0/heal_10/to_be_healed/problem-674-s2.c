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
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
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
    size_t word_len = strnlen(word, MAX_WORD_LENGTH);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(set->words[set->count], word, word_len);
    set->words[set->count][word_len] = '\0';
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
    size_t output_len = 0;
    token = strtok(temp, " ");

    while (token != NULL) {
        size_t token_len = strnlen(token, MAX_WORD_LENGTH);
        if (token_len < MAX_WORD_LENGTH && add_word(&set, token)) {
            size_t len = token_len;
            /* Possible weaknesses found:
             *  Common realloc mistake: 'output' nulled but not freed upon failure [memleakOnRealloc]
             */
            output = realloc(output, (output_len + len + 2) * sizeof(char));
            if (output == NULL) {
                free(temp);
                free(result);
                return NULL;
            }
            memmove(output + output_len, token, len + 1);
            output[output_len + len] = ' ';
            output_len += len + 1;
        }
        token = strtok(NULL, " ");
    }

    if (output) {
        if (output_len > 0) output[output_len - 1] = '\0';
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
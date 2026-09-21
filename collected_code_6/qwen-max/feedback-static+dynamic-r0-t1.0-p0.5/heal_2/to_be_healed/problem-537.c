#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;

    char *copy_str = strdup(str);
    token = strtok(copy_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        bool found = false;
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                /* Possible weaknesses found:
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 */
                free(copy_str);
                return (char *)token;
            }
        }
        if (!found) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[word_count], token, MAX_WORD_LENGTH - 1);
            words[word_count][MAX_WORD_LENGTH - 1] = '\0';
            word_count++;
        }
        token = strtok(NULL, " ");
    }
    free(copy_str);
    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}
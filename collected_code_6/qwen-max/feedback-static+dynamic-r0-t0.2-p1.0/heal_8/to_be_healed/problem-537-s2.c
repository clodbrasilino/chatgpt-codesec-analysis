#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* find_first_repeated_word(const char *str) {
    const int max_words = 1024;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char **words = (char **)malloc(max_words * sizeof(char *));
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'calloc'
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     */
    bool *seen = (bool *)calloc(max_words, sizeof(bool));
    int word_count = 0;

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        if (start == p) break;

        for (int i = 0; i < word_count; i++) {
            if (strncmp(words[i], start, p - start) == 0) {
                /* Possible weaknesses found:
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  include '<stdlib.h>' or provide a declaration of 'free'
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 */
                free(words);
                free(seen);
                return (char *)start;
            }
        }

        if (word_count < max_words) {
            words[word_count] = (char *)start;
            seen[word_count++] = true;
        } else {
            free(words);
            free(seen);
            return NULL;
        }

        if (*p) p++;
    }

    free(words);
    free(seen);
    return NULL;
}

int main() {
    const char *input = "ca ab bc ca";
    char *result = find_first_repeated_word(input);
    if (result) {
        const char *end = strchr(result, ' ');
        printf("First repeated word: %.*s\n", (int)(end ? end - result : strlen(result)), result);
    } else {
        printf("None\n");
    }

    const char *input2 = "a b c d e f g h i j k l m n o p q r s t u v w x y z a";
    result = find_first_repeated_word(input2);
    if (result) {
        const char *end = strchr(result, ' ');
        printf("First repeated word: %.*s\n", (int)(end ? end - result : strlen(result)), result);
    } else {
        printf("None\n");
    }

    const char *input3 = "unique words only";
    result = find_first_repeated_word(input3);
    if (result) {
        const char *end = strchr(result, ' ');
        printf("First repeated word: %.*s\n", (int)(end ? end - result : strlen(result)), result);
    } else {
        printf("None\n");
    }

    return 0;
}
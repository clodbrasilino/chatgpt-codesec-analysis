#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

char* findFirstRepeatedWord(const char* input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {""};
    int word_count = 0;
    /* Possible weaknesses found:
     *  Variable 'found' is assigned a value that is never used. [unreadVariable]
     */
    bool found = false;
    const char* p = input;
    const char* start = p;

    while (*p) {
        if (*p == ' ' || *p == '\n' || *p == '\t') {
            if (start != p) {
                for (int i = 0; i < word_count; ++i) {
                    if (strncmp(words[i], start, p - start) == 0) {
                        return strdup(start);
                    }
                }
                if (word_count < MAX_WORDS) {
                    strncpy(words[word_count], start, p - start);
                    words[word_count++][p - start] = '\0';
                }
            }
            start = p + 1;
        }
        p++;
    }

    if (start != p) {
        for (int i = 0; i < word_count; ++i) {
            if (strncmp(words[i], start, p - start) == 0) {
                return strdup(start);
            }
        }
    }

    return NULL;
}

int main() {
    const char* input = "This is a test test string to find the first repeated word";
    char* result = findFirstRepeatedWord(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(result);
    } else {
        printf("No repeated words found.\n");
    }

    return 0;
}
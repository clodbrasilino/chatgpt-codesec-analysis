#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    int c;
    int first = 1;
    size_t capacity = 256;
    size_t length = 0;
    char *word = malloc(capacity);

    if (!word) {
        return 1;
    }

    printf("[");
    
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF) {
        if (isspace(c)) {
            if (length > 0) {
                word[length] = '\0';
                if (!first) {
                    printf(", ");
                }
                printf("'%s'", word);
                first = 0;
                length = 0;
            }
        } else {
            if (length + 1 >= capacity) {
                size_t new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    free(word);
                    return 1;
                }
                char *temp = realloc(word, new_capacity);
                if (!temp) {
                    free(word);
                    return 1;
                }
                word = temp;
                capacity = new_capacity;
            }
            word[length++] = (char)c;
        }
    }
    
    if (length > 0) {
        word[length] = '\0';
        if (!first) {
            printf(", ");
        }
        printf("'%s'", word);
    }
    
    printf("]\n");

    free(word);
    return 0;
}
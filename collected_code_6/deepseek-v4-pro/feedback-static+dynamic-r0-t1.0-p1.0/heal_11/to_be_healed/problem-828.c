#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void count_chars(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    if (str == NULL) {
        return;
    }

    for (const char *p = str; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            (*alphabets)++;
        }
        else if (isdigit((unsigned char)*p)) {
            (*digits)++;
        }
        else {
            (*specials)++;
        }
    }
}

int main(void) {
    char *str = NULL;
    size_t buffer_size = 0;
    int alphabets, digits, specials;

    printf("Enter a string: ");
    
    ssize_t read = getline(&str, &buffer_size, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(str);
        return 1;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'read>0' is not redundant
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && str != NULL) {
        /* Possible weaknesses found:
         *  Assignment 'len=(unsigned long)read', assigned value is greater than 0
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t len = (size_t)read;
        /* Possible weaknesses found:
         *  Condition 'len>0' is always true
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         */
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        }
    }

    count_chars(str, &alphabets, &digits, &specials);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);

    free(str);
    return 0;
}
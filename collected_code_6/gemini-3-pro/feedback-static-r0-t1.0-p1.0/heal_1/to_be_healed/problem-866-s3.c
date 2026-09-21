#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0; 
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[20];
    int i = 0;
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    while (month[i] != '\0' && i < 19) {
        lower_month[i] = tolower((unsigned char)month[i]);
        i++;
    }
    lower_month[i] = '\0';

    if (strcmp(lower_month, "january") == 0 || strcmp(lower_month, "jan") == 0 ||
        strcmp(lower_month, "march") == 0 || strcmp(lower_month, "mar") == 0 ||
        strcmp(lower_month, "may") == 0 ||
        strcmp(lower_month, "july") == 0 || strcmp(lower_month, "jul") == 0 ||
        strcmp(lower_month, "august") == 0 || strcmp(lower_month, "aug") == 0 ||
        strcmp(lower_month, "october") == 0 || strcmp(lower_month, "oct") == 0 ||
        strcmp(lower_month, "december") == 0 || strcmp(lower_month, "dec") == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (has_31_days(input)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}
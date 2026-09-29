#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    int in_word = 0;
    /* Possible weaknesses found:
     *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'word_start' can be reduced. [variableScope]
     */
    size_t word_start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                /* Possible weaknesses found:
                 *  Value stored to 'word_start' is never read [deadcode.DeadStores]
                 *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
                 */
                word_start = i;
                str[i] = toupper((unsigned char)str[i]);
            }
        } else {
            if (in_word) {
                in_word = 0;
                str[i - 1] = toupper((unsigned char)str[i - 1]);
            }
        }
    }
}

int main(void) {
    char str1[] = "hello world! this is a test.";
    
    capitalize_first_and_last(str1);
    printf("%s\n", str1);

    char *str2 = malloc(50 * sizeof(char));
    if (str2 != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(str2, "c programming is fun", 49);
        str2[49] = '\0';
        capitalize_first_and_last(str2);
        printf("%s\n", str2);
        free(str2);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
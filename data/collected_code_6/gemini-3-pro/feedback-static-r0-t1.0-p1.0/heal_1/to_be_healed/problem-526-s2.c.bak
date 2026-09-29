#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    int in_word = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'word_start' can be reduced. [variableScope]
     *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
     */
    size_t word_start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                /* Possible weaknesses found:
                 *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'word_start' is never read [deadcode.DeadStores]
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
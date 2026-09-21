#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    int in_word = 0;
    size_t i = 0;

    while (1) {
        if (isalpha((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                str[i] = toupper((unsigned char)str[i]);
            }
        } else {
            if (in_word) {
                in_word = 0;
                if (i > 0) {
                    str[i - 1] = toupper((unsigned char)str[i - 1]);
                }
            }
        }
        
        if (str[i] == '\0') {
            break;
        }
        i++;
    }
}

int main(void) {
    char str1[] = "hello world! this is a test.";
    
    capitalize_first_and_last(str1);
    printf("%s\n", str1);

    char *str2 = malloc(50 * sizeof(char));
    if (str2 != NULL) {
        snprintf(str2, 50, "%s", "c programming is fun");
        capitalize_first_and_last(str2);
        printf("%s\n", str2);
        free(str2);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
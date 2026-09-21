#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    int in_word = 0;

    for (size_t i = 0; ; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            if (!in_word) {
                in_word = 1;
                str[i] = toupper(c);
            }
        } else {
            if (in_word) {
                in_word = 0;
                str[i - 1] = toupper((unsigned char)str[i - 1]);
            }
        }
        if (c == '\0') {
            break;
        }
    }
}

int main(void) {
    char str1[] = "hello world! this is a test.";
    
    capitalize_first_and_last(str1);
    printf("%s\n", str1);

    char *str2 = malloc(50 * sizeof(char));
    if (str2 != NULL) {
        snprintf(str2, 50, "c programming is fun");
        capitalize_first_and_last(str2);
        printf("%s\n", str2);
        free(str2);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
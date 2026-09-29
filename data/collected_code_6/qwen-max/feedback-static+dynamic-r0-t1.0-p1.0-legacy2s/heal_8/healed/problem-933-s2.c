#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *str) {
    const int buffer_size = 256;
    char *snake_case = (char *)malloc(buffer_size * sizeof(char));
    if (!snake_case) {
        return NULL;
    }
    snake_case[0] = '\0';

    int pos = 0;
    while (str[pos]) {
        if (isupper((unsigned char)str[pos])) {
            if (pos > 0 && str[pos-1] != '_') {
                strcat(snake_case, "_");
            }
            char lower_ch = tolower((unsigned char)str[pos]);
            char temp[2] = { lower_ch, '\0' };
            strcat(snake_case, temp);
        } else {
            char temp[2] = { str[pos], '\0' };
            strcat(snake_case, temp);
        }
        pos++;
    }

    return snake_case;
}

int main() {
    const char *test_cases[] = {"chromeCast", "quadCore", "googleAssistant"};
    const char *expected[] = {"chrome_cast", "quad_core", "google_assistant"};

    for (int i = 0; i < 3; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result) {
            printf("Expected: %s, Got: %s\n", expected[i], result);
            free(result);
        } else {
            printf("Conversion failed for: %s\n", test_cases[i]);
        }
    }

    return 0;
}
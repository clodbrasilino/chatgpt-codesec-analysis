#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    size_t upper_count = 0;

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            upper_count++;
        }
    }

    char *snake = malloc(len + upper_count + 1);
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            if (i > 0) {
                snake[j++] = '_';
            }
            snake[j++] = tolower((unsigned char)camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0';

    return snake;
}

int main(void) {
    const char *input1 = "camelCaseString";
    char *output1 = camel_to_snake(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "AnotherExample";
    char *output2 = camel_to_snake(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}
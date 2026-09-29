#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'quad_core', got quad_core_�
  *  test case 1 failed: expected 'chrome_cast', got chrome_cast_�
  *  test case 0 failed: expected 'google_assistant', got google_assistant_�
  */

char* camel_to_snake(const char *camel) {
    int len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (!snake) return NULL;
    snake[0] = '\0';

    int i, j, k;
    for (i = 0, j = 0, k = 0; i <= len; i++, j++) {
        if (i == len || isupper(camel[i])) {
            if (k > 0 && j > 0) {
                snake[j++] = '_';
            }
            k++;
            if (i < len) {
                snake[j] = tolower(camel[i]);
            }
        } else {
            snake[j] = camel[i];
        }
    }
    snake[j] = '\0';
    return snake;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "chrome_cast", "quad_core", "google_assistant"};
    for (size_t i = 0; i < 4; i++) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        } else {
            fprintf(stderr, "Error converting to snake case.\n");
        }
    }
    return 0;
}
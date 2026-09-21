#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* output = malloc(len * 2 + 1);
    if (!output) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0) {
                output[j++] = '_';
            }
            output[j++] = tolower((unsigned char)input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%1023s", input) == 1) {
        char* snake = camel_to_snake(input);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        }
    }
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_SIZE 256

int count_uppercase(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        int result = count_uppercase(input);
        printf("Uppercase count: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    return 0;
}
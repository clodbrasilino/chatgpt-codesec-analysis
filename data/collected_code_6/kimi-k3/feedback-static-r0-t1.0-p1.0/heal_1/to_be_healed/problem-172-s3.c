#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    if (len < 3) {
        return 0;
    }

    for (size_t i = 0; i <= len - 3; i++) {
        if (str[i] == 's' && str[i + 1] == 't' && str[i + 2] == 'd') {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *input = "std string with std occurrences std";
    int result = count_std_occurrences(input);

    if (result >= 0) {
        printf("Occurrences of 'std': %d\n", result);
    } else {
        printf("Invalid input string\n");
    }

    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *camel_to_snake(const char *str, char *result, size_t result_size) {
    if (str == NULL || result == NULL || result_size == 0) return NULL;
    size_t i, j = 0;
    for (i = 0; str[i] && j < result_size - 1; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != ' ') {
                if (j + 2 < result_size) {
                    result[j++] = '_';
                } else {
                    break;
                }
            }
            if (j + 1 < result_size) {
                result[j++] = tolower((unsigned char)str[i]);
            } else {
                break;
            }
        } else {
            if (j + 1 < result_size) {
                result[j++] = str[i];
            } else {
                break;
            }
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char input[] = "ThisIsCamelCase";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[30];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) < sizeof(output)) {
        camel_to_snake(input, output, sizeof(output));
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Input string is too long\n");
    }
    return 0;
}
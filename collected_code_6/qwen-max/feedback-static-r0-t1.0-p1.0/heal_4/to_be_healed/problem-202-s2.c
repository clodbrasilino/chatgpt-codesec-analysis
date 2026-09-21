#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[len];
    int j = 0;
    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if ((i + 1) % 2 != 0) {
            if (j < len - 1) {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(str, result, strlen(result) + 1);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[50];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        remove_even_characters(str, sizeof(str));
        printf("String after removing even characters: %s\n", str);
    }
    return 0;
}
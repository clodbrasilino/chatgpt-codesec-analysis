#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if ((i + 1) % 2 != 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[50];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline from fgets

    remove_even_characters(str);
    printf("String after removing even characters: %s\n", str);

    return 0;
}
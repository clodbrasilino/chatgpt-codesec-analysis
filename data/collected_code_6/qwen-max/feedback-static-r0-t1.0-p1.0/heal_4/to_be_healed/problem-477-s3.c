#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_lower_case(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len >= 99) {
            input[99] = '\0';
        } else {
            input[len] = '\0';
        }
        to_lower_case(input);
        printf("Lowercase string: %s\n", input);
    }
    return 0;
}
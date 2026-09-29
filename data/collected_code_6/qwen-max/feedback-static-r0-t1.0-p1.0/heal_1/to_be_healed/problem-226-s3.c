#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        remove_odd_index_chars(input);
        printf("Modified string: %s\n", input);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}
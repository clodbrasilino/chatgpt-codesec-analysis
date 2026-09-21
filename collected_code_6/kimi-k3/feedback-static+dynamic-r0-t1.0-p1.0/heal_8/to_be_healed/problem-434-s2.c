#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }
    int i = 1;
    while (str[i] == 'b') {
        i++;
    }
    return i > 1 && str[i] == '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';
    if (match(str)) {
        printf("Match found\n");
    } else {
        printf("No match\n");
    }
    return 0;
}
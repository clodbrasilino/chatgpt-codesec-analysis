#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[100] = "";
    int i, j = 0;
    for (i = 0; str[i] != '\0' && j < sizeof(result) - 2; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     *  use of undeclared identifier 'input'
     *  'input' undeclared (first use in this function); did you mean 'int'?
     */
    strncpy(str, result, sizeof(input) - 1);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'input'
     */
    str[sizeof(input) - 1] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        remove_odd_index_chars(input);
        printf("Modified string: %s\n", input);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}
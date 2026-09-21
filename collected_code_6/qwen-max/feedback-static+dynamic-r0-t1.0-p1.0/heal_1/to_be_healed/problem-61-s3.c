#include <stdio.h>
#include <string.h>

int countSubstrings(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str), count = 0;
    for (int i = 0; i < len; i++) {
        int sum = 0, j = 0;
        while (i + j < len && (sum + (str[i + j] - '0')) <= (j + 1)) {
            sum += str[i + j] - '0';
            if (sum == j + 1) {
                count++;
            }
            j++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
     */
    scanf("%s", input);
    int result = countSubstrings(input);
    printf("Count of substrings: %d\n", result);
    return 0;
}
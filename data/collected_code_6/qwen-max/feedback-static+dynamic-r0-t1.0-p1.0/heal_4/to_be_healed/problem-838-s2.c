#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int minSwapsToEqual(const char *a, const char *b) {
    int count01 = 0, count10 = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '0' && b[i] == '1') {
            count01++;
        } else if (a[i] == '1' && b[i] == '0') {
            count10++;
        }
    }
    if ((count01 + count10) % 2 != 0) {
        return -1;
    }
    return (count01 + count10) / 2;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char a[100], b[100];
    /* Possible weaknesses found:
     *  Unused variable: len [unusedVariable]
     */
    size_t len;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", a) != 1 || scanf("%99s", b) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(a) != strlen(b)) {
        printf("Strings are of different lengths.\n");
        return 1;
    }

    int result = minSwapsToEqual(a, b);

    if (result == -1) {
        printf("Strings cannot be made equal by swapping\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}
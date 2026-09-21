#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int get_demlo_number(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 1;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[22];
    snprintf(num_str, sizeof(num_str), "%d", n);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(num_str);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp_final_num[41];
        snprintf(temp_final_num, sizeof(temp_final_num), "%s%c", final_num, num_str[i]);
        for (int j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  Undefined behavior: Variable 'temp_final_num' is used as parameter and destination in snprintf(). [sprintfOverlappingData]
             */
            snprintf(temp_final_num, sizeof(temp_final_num), "%s%c", temp_final_num, num_str[len - j - 1]);
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(final_num, temp_final_num, sizeof(final_num) - 1);
        final_num[sizeof(final_num) - 1] = '\0';
    }

    return atoll(final_num);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    long long int result = get_demlo_number(number);
    if (result != -1) {
        printf("Demlo number: %lld\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
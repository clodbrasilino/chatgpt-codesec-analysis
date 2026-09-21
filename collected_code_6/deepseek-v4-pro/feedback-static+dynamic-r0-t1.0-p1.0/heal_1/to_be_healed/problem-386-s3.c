#include <stdio.h>
#include <string.h>

int minSwapsForBalance(const char *str) {
    int balance = 0;
    int swaps = 0;
    int start = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int end = strlen(str) - 1;

    while (start < end) {
        if (str[start] == '[') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            while (start < end && str[end] != '[') {
                end--;
            }
            char temp = str[start];
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            ((char *)str)[start] = str[end];
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            ((char *)str)[end] = temp;
            swaps++;
            balance = 1;
            end--;
        }
        start++;
    }

    return swaps;
}

int main(void) {
    const char *test1 = "]][[";
    const char *test2 = "[]][][";
    const char *test3 = "[[][]]";
    const char *test4 = "][";

    printf("Minimum swaps for \"%s\": %d\n", test1, minSwapsForBalance(test1));
    printf("Minimum swaps for \"%s\": %d\n", test2, minSwapsForBalance(test2));
    printf("Minimum swaps for \"%s\": %d\n", test3, minSwapsForBalance(test3));
    printf("Minimum swaps for \"%s\": %d\n", test4, minSwapsForBalance(test4));

    return 0;
}
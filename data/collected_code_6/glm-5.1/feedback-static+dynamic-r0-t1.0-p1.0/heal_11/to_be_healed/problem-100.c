#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void increment_mid_and_propagate(size_t *len, char *str, size_t capacity) {
    size_t mid = *len / 2;
    int64_t left = mid - 1;
    int64_t right = (*len % 2) ? mid + 1 : mid;
    bool left_smaller = false;

    while (left >= 0 && str[left] == str[right]) {
        left--;
        right++;
    }

    if (left < 0 || str[left] < str[right]) {
        left_smaller = true;
    }

    left = mid - 1;
    right = (*len % 2) ? mid + 1 : mid;

    while (left >= 0) {
        str[right] = str[left];
        left--;
        right++;
    }

    if (left_smaller) {
        int carry = 1;
        if (*len % 2 == 1) {
            int digit = str[mid] - '0' + carry;
            carry = digit / 10;
            str[mid] = (digit % 10) + '0';
        }
        left = mid - 1;
        right = (*len % 2) ? mid + 1 : mid;

        while (left >= 0 && carry > 0) {
            int digit = str[left] - '0' + carry;
            carry = digit / 10;
            str[left] = (digit % 10) + '0';
            str[right] = str[left];
            left--;
            right++;
        }

        if (carry > 0) {
            if (*len + 2 <= capacity) {
                memmove(str + 2, str + 1, *len - 1);
                str[0] = '1';
                str[*len] = '1';
                str[*len + 1] = '\0';
                *len = *len + 2;
            }
        }
    }
}

void next_smallest_palindrome(char *str, size_t capacity) {
    if (str == NULL || capacity == 0) {
        return;
    }

    size_t len = strnlen(str, capacity);
    if (len == 0 || len >= capacity) {
        return;
    }

    bool all_nine = true;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '9') {
            all_nine = false;
            break;
        }
    }

    if (all_nine) {
        if (len + 2 <= capacity) {
            str[0] = '1';
            for (size_t i = 1; i < len; i++) {
                str[i] = '0';
            }
            str[len] = '1';
            str[len + 1] = '\0';
        }
        return;
    }

    increment_mid_and_propagate(&len, str, capacity);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer1[128];
    snprintf(buffer1, sizeof(buffer1), "%s", "12345");
    next_smallest_palindrome(buffer1, sizeof(buffer1));
    printf("%s\n", buffer1);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer2[128];
    snprintf(buffer2, sizeof(buffer2), "%s", "999");
    next_smallest_palindrome(buffer2, sizeof(buffer2));
    printf("%s\n", buffer2);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer3[128];
    snprintf(buffer3, sizeof(buffer3), "%s", "23545");
    next_smallest_palindrome(buffer3, sizeof(buffer3));
    printf("%s\n", buffer3);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer4[128];
    snprintf(buffer4, sizeof(buffer4), "%s", "94187978322");
    next_smallest_palindrome(buffer4, sizeof(buffer4));
    printf("%s\n", buffer4);

    return 0;
}
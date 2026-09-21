#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_copy(char *dest, const char *src, int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[len - 1 - i];
    }
}

static void generate_next_palindrome(char *num, int len) {
    int mid = len / 2;
    int i = mid - 1;
    int j = (len % 2 == 0) ? mid : mid + 1;
    int left_smaller = 0;

    while (i >= 0 && num[i] == num[j]) {
        i--;
        j++;
    }

    if (i < 0 || num[i] < num[j]) {
        left_smaller = 1;
    }

    i = mid - 1;
    j = (len % 2 == 0) ? mid : mid + 1;

    while (i >= 0) {
        num[j] = num[i];
        j++;
        i--;
    }

    if (left_smaller) {
        int carry = 1;
        i = mid - 1;

        if (len % 2 == 1) {
            int digit = (num[mid] - '0') + carry;
            if (digit == 10) {
                num[mid] = '0';
                carry = 1;
            } else {
                num[mid] = digit + '0';
                carry = 0;
            }
            j = mid + 1;
        } else {
            j = mid;
        }

        while (i >= 0) {
            int digit = (num[i] - '0') + carry;
            if (digit == 10) {
                num[i] = '0';
                carry = 1;
            } else {
                num[i] = digit + '0';
                carry = 0;
            }
            num[j++] = num[i--];
        }
    }
}

static int handle_all_nines(char *num, int len, size_t buf_size) {
    size_t needed = (size_t)len + 2;
    if (needed > buf_size) {
        return 0;
    }
    num[0] = '1';
    for (int i = 1; i < len; i++) {
        num[i] = '0';
    }
    num[len] = '1';
    num[len + 1] = '\0';
    return 1;
}

static int is_all_nines(const char *num, int len) {
    for (int i = 0; i < len; i++) {
        if (num[i] != '9') {
            return 0;
        }
    }
    return 1;
}

char* next_smallest_palindrome(char *num, size_t buf_size) {
    if (buf_size == 0 || num == NULL) {
        return num;
    }

    size_t len = strnlen(num, buf_size);
    if (len == 0 || len >= buf_size) {
        return num;
    }

    int int_len = (int)len;

    if (is_all_nines(num, int_len)) {
        if (!handle_all_nines(num, int_len, buf_size)) {
            return num;
        }
        return num;
    }

    generate_next_palindrome(num, int_len);
    return num;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test1[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test2[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test3[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test4[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test5[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test6[64] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test7[64] = {0};

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test1, "123", sizeof(test1) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test2, "999", sizeof(test2) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test3, "1234", sizeof(test3) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test4, "9999", sizeof(test4) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test5, "100", sizeof(test5) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test6, "12921", sizeof(test6) - 1);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(test7, "125322", sizeof(test7) - 1);

    printf("Next palindrome of %s is %s\n", "123", next_smallest_palindrome(test1, sizeof(test1)));
    printf("Next palindrome of %s is %s\n", "999", next_smallest_palindrome(test2, sizeof(test2)));
    printf("Next palindrome of %s is %s\n", "1234", next_smallest_palindrome(test3, sizeof(test3)));
    printf("Next palindrome of %s is %s\n", "9999", next_smallest_palindrome(test4, sizeof(test4)));
    printf("Next palindrome of %s is %s\n", "100", next_smallest_palindrome(test5, sizeof(test5)));
    printf("Next palindrome of %s is %s\n", "12921", next_smallest_palindrome(test6, sizeof(test6)));
    printf("Next palindrome of %s is %s\n", "125322", next_smallest_palindrome(test7, sizeof(test7)));

    return 0;
}
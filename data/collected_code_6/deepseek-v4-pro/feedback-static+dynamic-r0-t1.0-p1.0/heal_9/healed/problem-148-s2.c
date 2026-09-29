#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

static int digit_sum(long long n) {
    int sum = 0;
    if (n < 0) n = -n;
    while (n > 0) {
        sum += (int)(n % 10);
        n /= 10;
    }
    return sum;
}

static long long safe_atoll(const char *str, int *valid) {
    char *endptr;
    errno = 0;
    long long val = strtoll(str, &endptr, 10);
    if (errno != 0 || endptr == str || *endptr != '\0') {
        *valid = 0;
        return 0;
    }
    *valid = 1;
    return val;
}

static void maximize_digit_sum(long long n, long long *part1, long long *part2) {
    char num_str[64];
    char part1_str[64];
    char part2_str[64];
    char temp1[64];
    char temp2[64];

    if (n < 0) {
        *part1 = 0;
        *part2 = 0;
        return;
    }

    if (n < 10) {
        *part1 = 0;
        *part2 = n;
        return;
    }

    int written = snprintf(num_str, sizeof(num_str), "%lld", n);
    if (written < 0 || (size_t)written >= sizeof(num_str)) {
        *part1 = 0;
        *part2 = 0;
        return;
    }

    size_t len = (size_t)written;
    if (len == 0 || len >= sizeof(num_str)) {
        *part1 = 0;
        *part2 = 0;
        return;
    }

    memset(part1_str, 0, sizeof(part1_str));
    memset(part2_str, 0, sizeof(part2_str));

    long long best_sum = -1;
    long long best_p1 = 0;
    long long best_p2 = 0;

    for (size_t i = 1; i < len; i++) {
        if (num_str[i - 1] == '0') continue;

        memset(temp1, 0, sizeof(temp1));
        memset(temp2, 0, sizeof(temp2));

        size_t copy_len = i;
        if (copy_len >= sizeof(temp1)) copy_len = sizeof(temp1) - 1;
        if (copy_len > 0) {
            memcpy(temp1, num_str, copy_len);
        }
        temp1[copy_len] = '\0';

        if (num_str[i - 1] > '1') {
            size_t borrow_idx = i - 1;
            while (borrow_idx > 0 && borrow_idx < sizeof(temp1) && temp1[borrow_idx] == '0') {
                temp1[borrow_idx] = '9';
                borrow_idx--;
            }
            if (borrow_idx < sizeof(temp1) && temp1[borrow_idx] >= '1') {
                temp1[borrow_idx]--;
            }
        }

        size_t k = 0;
        while (k < i && k < sizeof(temp1) && temp1[k] == '0') k++;
        size_t start1 = k;
        if (start1 >= i) start1 = 0;

        size_t t2_idx = 0;
        int leading_zero = 1;
        for (size_t j = i; j < len; j++) {
            if (leading_zero && num_str[j] == '0') continue;
            leading_zero = 0;
            if (t2_idx >= sizeof(temp2) - 1) break;
            temp2[t2_idx++] = num_str[j];
        }
        temp2[t2_idx] = '\0';

        int found_non_nine = 0;
        for (size_t j = i; j < len; j++) {
            if (num_str[j] != '9') {
                size_t idx = j - i;
                if (idx < sizeof(temp2) - 1) {
                    temp2[idx] = '9';
                    temp2[idx + 1] = '\0';
                }
                found_non_nine = 1;
                break;
            }
        }

        if (!found_non_nine && t2_idx == 0) {
            temp2[0] = '0';
            temp2[1] = '\0';
        }

        size_t temp1_start_offset = start1;
        if (temp1_start_offset >= sizeof(temp1)) temp1_start_offset = sizeof(temp1) - 1;
        size_t temp1_remaining = sizeof(temp1) - temp1_start_offset;
        size_t temp1_len = strnlen(temp1 + temp1_start_offset, temp1_remaining);

        size_t temp2_len = strnlen(temp2, sizeof(temp2));

        if (temp1_len == 0 && temp1_start_offset < sizeof(temp1)) {
            if (temp1_start_offset + 1 < sizeof(temp1)) {
                temp1[temp1_start_offset] = '0';
                temp1[temp1_start_offset + 1] = '\0';
                temp1_len = 1;
            }
        }
        if (temp2_len == 0 && sizeof(temp2) > 0) {
            temp2[0] = '0';
            temp2[1] = '\0';
            temp2_len = 1;
        }

        int valid_t1 = 0, valid_t2 = 0;
        long long t1 = safe_atoll(temp1 + temp1_start_offset, &valid_t1);
        long long t2 = safe_atoll(temp2, &valid_t2);
        if (!valid_t1 || !valid_t2) continue;

        long long current_sum = digit_sum(t1) + digit_sum(t2);

        if (current_sum > best_sum) {
            best_sum = current_sum;
            best_p1 = t1;
            best_p2 = t2;
            if (temp1_len < sizeof(part1_str)) {
                size_t max_copy1 = temp1_len;
                if (max_copy1 >= sizeof(part1_str)) max_copy1 = sizeof(part1_str) - 1;
                memcpy(part1_str, temp1 + temp1_start_offset, max_copy1);
                part1_str[max_copy1] = '\0';
            }
            if (temp2_len < sizeof(part2_str)) {
                size_t max_copy2 = temp2_len;
                if (max_copy2 >= sizeof(part2_str)) max_copy2 = sizeof(part2_str) - 1;
                memcpy(part2_str, temp2, max_copy2);
                part2_str[max_copy2] = '\0';
            }
        } else if (current_sum == best_sum) {
            if (t1 > best_p1 || (t1 == best_p1 && t2 > best_p2)) {
                best_p1 = t1;
                best_p2 = t2;
                if (temp1_len < sizeof(part1_str)) {
                    size_t max_copy1 = temp1_len;
                    if (max_copy1 >= sizeof(part1_str)) max_copy1 = sizeof(part1_str) - 1;
                    memcpy(part1_str, temp1 + temp1_start_offset, max_copy1);
                    part1_str[max_copy1] = '\0';
                }
                if (temp2_len < sizeof(part2_str)) {
                    size_t max_copy2 = temp2_len;
                    if (max_copy2 >= sizeof(part2_str)) max_copy2 = sizeof(part2_str) - 1;
                    memcpy(part2_str, temp2, max_copy2);
                    part2_str[max_copy2] = '\0';
                }
            }
        }
    }

    if (best_sum == -1) {
        part1_str[0] = '0';
        part1_str[1] = '\0';
        snprintf(part2_str, sizeof(part2_str), "%lld", n);
    }

    int valid_p1 = 0, valid_p2 = 0;
    *part1 = safe_atoll(part1_str, &valid_p1);
    *part2 = safe_atoll(part2_str, &valid_p2);
    if (!valid_p1) *part1 = 0;
    if (!valid_p2) *part2 = n;
}

int main(void) {
    long long test_numbers[] = {123456, 1000, 999, 54321, 100000, 7, 0, 987654321};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (int i = 0; i < num_tests; i++) {
        long long n = test_numbers[i];
        long long part1, part2;
        maximize_digit_sum(n, &part1, &part2);
        printf("Number: %lld -> Parts: %lld + %lld, Digit Sum: %d\n",
               n, part1, part2, digit_sum(part1) + digit_sum(part2));
    }

    return 0;
}
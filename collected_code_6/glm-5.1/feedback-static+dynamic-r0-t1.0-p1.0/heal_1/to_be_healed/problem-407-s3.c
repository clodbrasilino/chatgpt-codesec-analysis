#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool next_bigger_number(long long n, long long *result) {
    if (n < 0) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[32];
    snprintf(buf, sizeof(buf), "%lld", n);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buf);

    long long i = (long long)len - 2;
    while (i >= 0 && buf[i] >= buf[i + 1]) {
        i--;
    }

    if (i < 0) {
        return false;
    }

    long long j = (long long)len - 1;
    while (buf[j] <= buf[i]) {
        j--;
    }

    char temp = buf[i];
    buf[i] = buf[j];
    buf[j] = temp;

    size_t left = (size_t)(i + 1);
    size_t right = len - 1;
    while (left < right) {
        temp = buf[left];
        buf[left] = buf[right];
        buf[right] = temp;
        left++;
        right--;
    }

    char *endptr = NULL;
    errno = 0;
    long long val = strtoll(buf, &endptr, 10);

    if (errno == ERANGE || endptr == buf || *endptr != '\0') {
        return false;
    }

    *result = val;
    return true;
}

int main(void) {
    long long input;
    long long output;

    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (next_bigger_number(input, &output)) {
        printf("%lld\n", output);
    } else {
        printf("-1\n");
    }

    return 0;
}
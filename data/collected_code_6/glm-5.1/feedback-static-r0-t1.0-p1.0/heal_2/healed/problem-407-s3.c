#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool next_bigger_number(long long n, long long *result) {
    if (n < 0) {
        return false;
    }

    size_t buf_size = 32;
    char *buf = malloc(buf_size);
    if (!buf) {
        return false;
    }

    int written = snprintf(buf, buf_size, "%lld", n);
    if (written < 0 || (size_t)written >= buf_size) {
        buf_size = (size_t)written + 1;
        char *new_buf = realloc(buf, buf_size);
        if (!new_buf) {
            free(buf);
            return false;
        }
        buf = new_buf;
        snprintf(buf, buf_size, "%lld", n);
    }

    size_t len = (size_t)written;

    if (len < 2) {
        free(buf);
        return false;
    }

    size_t i = len - 2;
    while (i != (size_t)-1 && buf[i] >= buf[i + 1]) {
        i--;
    }

    if (i == (size_t)-1) {
        free(buf);
        return false;
    }

    size_t j = len - 1;
    while (buf[j] <= buf[i]) {
        j--;
    }

    char temp = buf[i];
    buf[i] = buf[j];
    buf[j] = temp;

    size_t left = i + 1;
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

    free(buf);

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
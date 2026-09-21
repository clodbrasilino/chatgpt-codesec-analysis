#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int find_numbers(long long left, long long right,
                        long long *first, long long *second)
{
    if (first == NULL || second == NULL || left <= 0 || right < left) {
        return 0;
    }

    if (left <= right / 2) {
        *first = left;
        *second = left * 2;
        return 1;
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *cursor;
    char *end;
    long long left;
    long long right;
    long long first;
    long long second;
    int status = EXIT_FAILURE;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    cursor = line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    left = strtoll(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        goto cleanup;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    right = strtoll(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (find_numbers(left, right, &first, &second)) {
        if (printf("%lld %lld\n", first, second) < 0) {
            goto cleanup;
        }
    } else {
        if (printf("-1 -1\n") < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    return status;
}
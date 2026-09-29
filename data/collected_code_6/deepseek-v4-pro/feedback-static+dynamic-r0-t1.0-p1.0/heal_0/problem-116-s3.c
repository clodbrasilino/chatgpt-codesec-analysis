#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

long long tuple_to_int(const int *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        errno = EINVAL;
        return 0;
    }

    size_t total_len = 1;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] < 0) {
            errno = EINVAL;
            return 0;
        }
        int tmp = tuple[i];
        int digits = 1;
        while (tmp >= 10) {
            tmp /= 10;
            digits++;
        }
        if (total_len > SIZE_MAX - digits - 1) {
            errno = EOVERFLOW;
            return 0;
        }
        total_len += digits;
    }

    char *buffer = (char *)malloc(total_len);
    if (buffer == NULL) {
        errno = ENOMEM;
        return 0;
    }

    size_t pos = 0;
    for (size_t i = 0; i < size; i++) {
        int written = snprintf(buffer + pos, total_len - pos, "%d", tuple[i]);
        if (written < 0 || (size_t)written >= total_len - pos) {
            free(buffer);
            errno = EOVERFLOW;
            return 0;
        }
        pos += (size_t)written;
    }
    buffer[pos] = '\0';

    errno = 0;
    char *endptr = NULL;
    long long result = strtoll(buffer, &endptr, 10);

    if (errno == ERANGE) {
        free(buffer);
        return 0;
    }
    if (endptr == buffer || *endptr != '\0') {
        free(buffer);
        errno = EINVAL;
        return 0;
    }

    free(buffer);
    return result;
}

int main(void) {
    int tuple1[] = {12, 34, 56};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    errno = 0;
    long long result1 = tuple_to_int(tuple1, size1);
    if (errno == 0) {
        printf("%lld\n", result1);
    } else {
        printf("Error: %d\n", errno);
    }

    int tuple2[] = {1, 23, 456, 7890};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    errno = 0;
    long long result2 = tuple_to_int(tuple2, size2);
    if (errno == 0) {
        printf("%lld\n", result2);
    } else {
        printf("Error: %d\n", errno);
    }

    int tuple3[] = {0, 0, 1};
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    errno = 0;
    long long result3 = tuple_to_int(tuple3, size3);
    if (errno == 0) {
        printf("%lld\n", result3);
    } else {
        printf("Error: %d\n", errno);
    }

    int tuple4[] = {-1, 2, 3};
    size_t size4 = sizeof(tuple4) / sizeof(tuple4[0]);
    errno = 0;
    long long result4 = tuple_to_int(tuple4, size4);
    if (errno == 0) {
        printf("%lld\n", result4);
    } else {
        printf("Error: %d\n", errno);
    }

    return 0;
}
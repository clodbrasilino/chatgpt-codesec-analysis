#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int check_tuples(const int *t1, const int *t2, size_t size) {
    if (t1 == NULL || t2 == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (t2[i] >= t1[i]) {
            return 0;
        }
    }
    return 1;
}

long safe_strtol(const char *str, int *err) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN || *endptr != '\0' || str == endptr) {
        *err = 1;
    }
    return val;
}

int main(int argc, char const *argv[]) {
    if (argc < 4 || (argc - 1) % 2 != 0) {
        fprintf(stderr, "Usage: %s t1_1 t1_2 ... t2_1 t2_2 ...\n", argv[0]);
        return 1;
    }

    size_t size = (argc - 1) / 2;

    int *t1 = malloc(size * sizeof(int));
    int *t2 = malloc(size * sizeof(int));

    if (t1 == NULL || t2 == NULL) {
        free(t1);
        free(t2);
        return 1;
    }

    int err = 0;
    for (size_t i = 0; i < size && !err; i++) {
        long val1 = safe_strtol(argv[1 + i], &err);
        if (!err) t1[i] = (int)val1;
        
        long val2 = safe_strtol(argv[1 + size + i], &err);
        if (!err) t2[i] = (int)val2;
    }

    if (err) {
        free(t1);
        free(t2);
        return 1;
    }

    int result = check_tuples(t1, t2, size);
    printf("%d\n", result);

    free(t1);
    free(t2);

    return 0;
}
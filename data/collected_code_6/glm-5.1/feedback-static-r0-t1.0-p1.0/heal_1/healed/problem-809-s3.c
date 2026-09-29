#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

int main(int argc, char * const argv[]) {
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

    for (size_t i = 0; i < size; i++) {
        char *endptr1;
        long val1 = strtol(argv[1 + i], &endptr1, 10);
        if (errno == ERANGE || val1 > INT_MAX || val1 < INT_MIN || *endptr1 != '\0' || argv[1 + i][0] == '\0') {
            free(t1);
            free(t2);
            return 1;
        }
        t1[i] = (int)val1;

        char *endptr2;
        errno = 0;
        long val2 = strtol(argv[1 + size + i], &endptr2, 10);
        if (errno == ERANGE || val2 > INT_MAX || val2 < INT_MIN || *endptr2 != '\0' || argv[1 + size + i][0] == '\0') {
            free(t1);
            free(t2);
            return 1;
        }
        t2[i] = (int)val2;
    }

    int result = check_tuples(t1, t2, size);
    printf("%d\n", result);

    free(t1);
    free(t2);

    return 0;
}
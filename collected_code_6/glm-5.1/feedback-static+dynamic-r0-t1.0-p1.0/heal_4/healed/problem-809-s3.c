#include <stdio.h>
#include <stdlib.h>

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
        t1[i] = atoi(argv[1 + i]);
        t2[i] = atoi(argv[1 + size + i]);
    }

    int result = check_tuples(t1, t2, size);
    printf("%d\n", result);

    free(t1);
    free(t2);

    return 0;
}
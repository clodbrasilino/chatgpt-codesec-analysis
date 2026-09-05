#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 't1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 't2' can be declared as pointer to const [constParameterPointer]
 */
int check_tuples(int *t1, int *t2, size_t size) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
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
#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'tuple2' can be declared as pointer to const [constParameterPointer]
 */
void multiplyTuples(int *tuple1, int *tuple2, int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -999 * -99999999 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000012,time:57511,execs:5271,op:havoc,rep:1)
         * UBSan: signed integer overflow: -1215752191 * -99 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000012,time:57908,execs:5429,op:havoc,rep:4)
         */
        result[i] = tuple1[i] * tuple2[i];
    }
}

int main() {
    size_t length;
    printf("Enter the length of the tuples: ");
    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *tuple1 = malloc(length * sizeof(int));
    int *tuple2 = malloc(length * sizeof(int));
    int *result = malloc(length * sizeof(int));

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple1);
        free(tuple2);
        free(result);
        return EXIT_FAILURE;
    }

    printf("Enter elements of first tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &tuple1[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(tuple1);
            free(tuple2);
            free(result);
            return EXIT_FAILURE;
        }
    }

    printf("Enter elements of second tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &tuple2[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(tuple1);
            free(tuple2);
            free(result);
            return EXIT_FAILURE;
        }
    }

    multiplyTuples(tuple1, tuple2, result, length);

    printf("Resultant tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(tuple1);
    free(tuple2);
    free(result);
    return EXIT_SUCCESS;
}
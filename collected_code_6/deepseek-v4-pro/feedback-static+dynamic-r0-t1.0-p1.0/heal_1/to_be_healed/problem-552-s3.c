#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'sequence' can be declared as pointer to const [constParameterPointer]
 */
bool is_linear_sequence(int *sequence, int length) {
    if (sequence == NULL || length < 2) {
        return length <= 1;
    }

    int difference = sequence[1] - sequence[0];

    for (int i = 2; i < length; i++) {
        if (sequence[i] - sequence[i - 1] != difference) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int length;

    printf("Enter the number of elements in the sequence: ");
    if (scanf("%d", &length) != 1 || length < 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    int *sequence = malloc((size_t)length * sizeof(int));
    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d integers:\n", length);
    for (int i = 0; i < length; i++) {
        if (scanf("%d", &sequence[i]) != 1) {
            printf("Invalid input.\n");
            free(sequence);
            return EXIT_FAILURE;
        }
    }

    if (is_linear_sequence(sequence, length)) {
        printf("The sequence is linear.\n");
    } else {
        printf("The sequence is not linear.\n");
    }

    free(sequence);
    return EXIT_SUCCESS;
}
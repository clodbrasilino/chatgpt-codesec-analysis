#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int is_number_greater(int *array, int array_size, int number) {
    for (int i = 0; i < array_size; ++i) {
        if (array[i] >= number) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int array_size = sizeof(array) / sizeof(array[0]);
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_number_greater(array, array_size, number)) {
        printf("The entered number is greater than all elements in the array.\n");
    } else {
        printf("The entered number is not greater than all elements in the array.\n");
    }

    return EXIT_SUCCESS;
}
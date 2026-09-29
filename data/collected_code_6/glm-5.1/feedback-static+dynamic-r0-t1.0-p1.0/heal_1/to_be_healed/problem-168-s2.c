#include <stdio.h>
#include <stdlib.h>

size_t find_frequency(const int *array, size_t size, int target) {
    size_t count = 0;
    if (array != NULL && size > 0) {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == target) {
                count++;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int target = atoi(argv[1]);

    int array[] = {1, 2, 3, 4, 2, 5, 2, 8, 9, 2};
    size_t size = sizeof(array) / sizeof(array[0]);

    size_t frequency = find_frequency(array, size, target);

    printf("%zu\n", frequency);

    return EXIT_SUCCESS;
}
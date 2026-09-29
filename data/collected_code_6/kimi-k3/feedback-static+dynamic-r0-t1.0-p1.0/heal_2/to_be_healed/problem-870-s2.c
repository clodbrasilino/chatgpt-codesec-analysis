#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 48, got <no output>
  *  test case 2 failed: expected 522, got <no output>
  *  test case 1 failed: expected 50, got <no output>
  */

double sum_positive(const double *numbers, size_t count)
{
    double sum = 0.0;
    size_t i;

    if (numbers == NULL) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    double *numbers;
    size_t count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    double result;

    if (argc > 1) {
        count = (size_t)(argc - 1);
        numbers = (double *)malloc(count * sizeof(double));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        for (i = 0; i < count; i++) {
            numbers[i] = atof(argv[i + 1]);
        }
    } else {
        static double default_numbers[] = {1.5, -2.0, 3.2, -4.8, 5.0};
        count = sizeof(default_numbers) / sizeof(default_numbers[0]);
        numbers = (double *)malloc(count * sizeof(double));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(numbers, default_numbers, count * sizeof(double));
    }

    result = sum_positive(numbers, count);

    printf("%.2f\n", result);

    free(numbers);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int first_missing_positive(int *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return 1;
    }

    for (i = 0U; i < count; ++i) {
        while (numbers[i] > 0 && (size_t)numbers[i] <= count) {
            size_t target = (size_t)numbers[i] - 1U;
            int temporary;

            if (numbers[target] == numbers[i]) {
                break;
            }

            temporary = numbers[i];
            numbers[i] = numbers[target];
            numbers[target] = temporary;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] <= 0 || (size_t)numbers[i] != i + 1U) {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'INT_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             */
            if (i >= (size_t)INT_MAX) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'INT_MAX'
                 */
                return INT_MAX;
            }
            return (int)(i + 1U);
        }
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     */
    if (count >= (size_t)INT_MAX) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        return INT_MAX;
    }

    return (int)(count + 1U);
}

int main(void)
{
    int numbers[] = {3, 4, -1, 1};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = first_missing_positive(numbers, count);

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
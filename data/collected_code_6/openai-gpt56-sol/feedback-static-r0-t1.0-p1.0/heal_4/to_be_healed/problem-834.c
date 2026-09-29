#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int generate_spiral_matrix(size_t n, unsigned long long **matrix)
{
    size_t count;
    size_t top = 0;
    size_t left = 0;
    size_t bottom;
    size_t right;
    unsigned long long value = 1;

    if (matrix == NULL) {
        return -1;
    }

    *matrix = NULL;

    if (n == 0 || n > SIZE_MAX / n) {
        return -1;
    }

    count = n * n;

    if (count > SIZE_MAX / sizeof **matrix ||
        count > ULLONG_MAX / count) {
        return -1;
    }

    *matrix = malloc(count * sizeof **matrix);
    if (*matrix == NULL) {
        return -1;
    }

    bottom = n - 1;
    right = n - 1;

    while (top <= bottom && left <= right) {
        size_t i;

        for (i = left; i <= right; ++i) {
            (*matrix)[top * n + i] = value * value;
            ++value;
        }
        ++top;

        for (i = top; i <= bottom; ++i) {
            (*matrix)[i * n + right] = value * value;
            ++value;
        }

        if (right == 0) {
            break;
        }
        --right;

        if (top <= bottom) {
            for (i = right + 1; i > left;) {
                --i;
                (*matrix)[bottom * n + i] = value * value;
                ++value;
            }

            if (bottom == 0) {
                break;
            }
            --bottom;
        }

        if (left <= right) {
            for (i = bottom + 1; i > top;) {
                --i;
                (*matrix)[i * n + left] = value * value;
                ++value;
            }
            ++left;
        }
    }

    return 0;
}

static int print_matrix(const unsigned long long *matrix, size_t n)
{
    size_t row;
    size_t column;

    if (matrix == NULL || n == 0) {
        return -1;
    }

    for (row = 0; row < n; ++row) {
        for (column = 0; column < n; ++column) {
            if (printf("%llu%c",
                       matrix[row * n + column],
                       column + 1 == n ? '\n' : ' ') < 0) {
                return -1;
            }
        }
    }

    return 0;
}

static int read_matrix_size(size_t *n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    unsigned long long parsed;

    if (n == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(buffer, '\n') == NULL) {
        /* Possible weaknesses found:
         *  The scope of the variable 'ch' can be reduced. [variableScope]
         */
        int ch;

        if (!feof(stdin)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (!isdigit((unsigned char)*start)) {
        return -1;
    }

    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    errno = 0;
    parsed = strtoull(start, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     */
    if (errno == ERANGE || end == start || parsed == 0) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    if (parsed > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    {
        size_t size = (size_t)parsed;
        size_t count;

        if (size > SIZE_MAX / size) {
            return -1;
        }

        count = size * size;

        if (count > SIZE_MAX / sizeof(unsigned long long) ||
            count > ULLONG_MAX / count) {
            return -1;
        }

        *n = size;
    }

    return 0;
}

int main(void)
{
    size_t n;
    unsigned long long *matrix = NULL;

    if (read_matrix_size(&n) != 0) {
        fputs("Invalid matrix size.\n", stderr);
        return EXIT_FAILURE;
    }

    if (generate_spiral_matrix(n, &matrix) != 0) {
        fputs("Unable to generate matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_matrix(matrix, n) != 0) {
        free(matrix);
        fputs("Unable to print matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    free(matrix);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

typedef struct {
    long first;
    long second;
} Tuple;

static Tuple maximize_tuples(Tuple left, Tuple right)
{
    Tuple result = {
        left.first > right.first ? left.first : right.first,
        left.second > right.second ? left.second : right.second
    };

    return result;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_long(long *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(long) * CHAR_BIT + 4];
    char *end;
    long parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        discard_line();
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    Tuple left;
    Tuple right;
    Tuple result;

    if (!read_long(&left.first) ||
        !read_long(&left.second) ||
        !read_long(&right.first) ||
        !read_long(&right.second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = maximize_tuples(left, right);

    if (printf("(%ld, %ld)\n", result.first, result.second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define INPUT_BUFFER_SIZE 256

static int calculate_profit(double cost, double revenue, double *profit)
{
    double result;

    if (profit == NULL ||
        !isfinite(cost) ||
        !isfinite(revenue) ||
        cost < 0.0 ||
        revenue < 0.0 ||
        revenue <= cost) {
        return 0;
    }

    result = revenue - cost;

    if (!isfinite(result)) {
        return 0;
    }

    *profit = result;
    return 1;
}

static int read_amount(const char *prompt, double *amount)
{
    char *buffer;
    char *end;
    char *newline;
    double value;
    size_t capacity;
    ssize_t length;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    buffer = NULL;
    capacity = 0;
    length = getline(&buffer, &capacity, stdin);

    if (length < 0) {
        free(buffer);
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    errno = 0;
    end = NULL;
    value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *amount = value;
    free(buffer);
    return 1;
}

int main(void)
{
    double cost;
    double revenue;
    double profit;

    if (!read_amount("Enter cost amount: ", &cost) ||
        !read_amount("Enter selling amount: ", &revenue)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, revenue, &profit)) {
        if (printf("Profit: %.2f\n", profit) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("none") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strchr'
 */
#include <stdint.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL ||
        !isfinite(cost_price) ||
        !isfinite(selling_price) ||
        cost_price < 0.0 ||
        selling_price < 0.0) {
        return 0;
    }

    if (cost_price > selling_price) {
        *loss = cost_price - selling_price;
        return 1;
    }

    *loss = 0.0;
    return 0;
}

static int read_amount(const char *prompt, double *amount)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    double value;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(buffer, '\n') == NULL) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    errno = 0;
    end = buffer;
    value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *amount = value;
    return 1;
}

int main(void)
{
    double cost_price;
    double selling_price;
    double loss;

    if (!read_amount("Enter cost price: ", &cost_price) ||
        !read_amount("Enter selling price: ", &selling_price)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_loss(cost_price, selling_price, &loss)) {
        printf("Loss amount: %.2f\n", loss);
    } else {
        puts("None");
    }

    return EXIT_SUCCESS;
}
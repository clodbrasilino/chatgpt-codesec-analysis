#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL ||
        !isfinite(cost_price) ||
        !isfinite(selling_price) ||
        cost_price < 0.0 ||
        selling_price < 0.0) {
        return 0;
    }

    *loss = cost_price > selling_price
          ? cost_price - selling_price
          : 0.0;

    return cost_price > selling_price;
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

static int read_amount(const char *prompt, double *amount)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double value;
    int ch;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *expanded;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                discard_line();
                return 0;
            }

            new_capacity = capacity == 0 ? 64 : capacity * 2;
            expanded = realloc(buffer, new_capacity);
            if (expanded == NULL) {
                free(buffer);
                discard_line();
                return 0;
            }

            buffer = expanded;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    if (length + 1 >= capacity) {
        char *expanded = realloc(buffer, length + 1);
        if (expanded == NULL) {
            free(buffer);
            return 0;
        }
        buffer = expanded;
    }

    buffer[length] = '\0';

    errno = 0;
    end = buffer;
    value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
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
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

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

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin);
}

static int read_amount(const char *prompt, double *amount)
{
    char *line = NULL;
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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_line;
        size_t new_capacity;

        if (length == capacity) {
            if (capacity > (SIZE_MAX - 1) / 2) {
                free(line);
                discard_line();
                return 0;
            }

            new_capacity = capacity == 0 ? 128 : capacity * 2;
            new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                discard_line();
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(line);
        return 0;
    }

    if (length == capacity) {
        char *new_line;

        if (capacity == SIZE_MAX) {
            free(line);
            return 0;
        }

        new_line = realloc(line, capacity + 1);
        if (new_line == NULL) {
            free(line);
            return 0;
        }

        line = new_line;
    }

    line[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *amount = value;
    free(line);
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
        printf("Profit: %.2f\n", profit);
    } else {
        puts("none");
    }

    return EXIT_SUCCESS;
}
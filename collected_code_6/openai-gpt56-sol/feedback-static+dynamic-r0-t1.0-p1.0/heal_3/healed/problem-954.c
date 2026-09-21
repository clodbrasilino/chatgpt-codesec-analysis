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

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    *line = NULL;
    *capacity = 0;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity == 0 ? 128 : *capacity * 2;
            char *new_line;

            if (new_capacity <= *capacity) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return 0;
    }

    if (length + 1 >= *capacity) {
        size_t new_capacity = length + 1;
        char *new_line = realloc(*line, new_capacity);

        if (new_line == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return 0;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    (*line)[length] = '\0';
    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    size_t capacity;
    double cost;
    double revenue;
    double profit;

    if (!read_line(&input, &capacity)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    start = input;
    cost = strtod(start, &end);
    if (end == start || errno == ERANGE || !isfinite(cost)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    start = end;
    revenue = strtod(start, &end);
    if (end == start || errno == ERANGE || !isfinite(revenue)) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_profit(cost, revenue, &profit)) {
        if (printf("%.2f\n", profit) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("none") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
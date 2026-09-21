#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

typedef struct {
    double A;
    double B;
    double C;
} Line;

static int find_directrix(const Parabola parabola, Line *const directrix)
{
    double denominator;
    double c;

    if (directrix == NULL ||
        !isfinite(parabola.a) ||
        !isfinite(parabola.b) ||
        !isfinite(parabola.c) ||
        parabola.a == 0.0) {
        return 0;
    }

    denominator = 4.0 * parabola.a;

    if (!isfinite(denominator) || denominator == 0.0) {
        return 0;
    }

    c = parabola.c -
        (parabola.b * parabola.b + 1.0) / denominator;

    if (!isfinite(c)) {
        return 0;
    }

    directrix->A = 0.0;
    directrix->B = 1.0;
    directrix->C = c;

    return 1;
}

static int parse_double(const char *const text, double *const value)
{
    char *end;
    double parsed_value;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed_value = strtod(text, &end);

    if (errno == ERANGE ||
        end == text ||
        end == NULL ||
        *end != '\0' ||
        !isfinite(parsed_value)) {
        return 0;
    }

    *value = parsed_value;
    return 1;
}

int main(int argc, char *argv[])
{
    Parabola parabola;
    Line directrix;
    const char *program_name;

    program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 4 || argv == NULL) {
        fprintf(stderr, "Usage: %s a b c\n", program_name);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL ||
        argv[2] == NULL ||
        argv[3] == NULL ||
        !parse_double(argv[1], &parabola.a) ||
        !parse_double(argv[2], &parabola.b) ||
        !parse_double(argv[3], &parabola.c)) {
        fputs("Error: a, b, and c must be finite numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_directrix(parabola, &directrix)) {
        fputs("Error: invalid parabola or non-finite result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g*x + %.17g*y + %.17g = 0\n",
               directrix.A, directrix.B, directrix.C) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
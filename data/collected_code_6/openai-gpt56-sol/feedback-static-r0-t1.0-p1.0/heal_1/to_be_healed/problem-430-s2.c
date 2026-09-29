#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

static int find_directrix(const Parabola *parabola, double *directrix)
{
    double discriminant;

    if (parabola == NULL || directrix == NULL ||
        !isfinite(parabola->a) || !isfinite(parabola->b) ||
        !isfinite(parabola->c) || parabola->a == 0.0) {
        return -1;
    }

    discriminant = parabola->b * parabola->b -
                   4.0 * parabola->a * parabola->c;

    if (!isfinite(discriminant)) {
        return -1;
    }

    *directrix = (discriminant - 1.0) / (4.0 * parabola->a);

    return isfinite(*directrix) ? 0 : -1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    Parabola parabola;
    double directrix;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &parabola.a) != 0 ||
        parse_double(argv[2], &parabola.b) != 0 ||
        parse_double(argv[3], &parabola.c) != 0) {
        fputs("Invalid coefficient.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_directrix(&parabola, &directrix) != 0) {
        fputs("Unable to determine the directrix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("y = %.17g\n", directrix) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
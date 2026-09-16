#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double calculate_dog_years(double human_years)
{
    if (human_years <= 2.0) {
        return human_years * 10.5;
    }

    return 21.0 + (human_years - 2.0) * 4.0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    char *end = NULL;
    double human_years;
    double dog_years;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <human_years>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    human_years = strtod(argv[1], &end);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(human_years) || human_years < 0.0) {
        fprintf(stderr, "Invalid age: enter a finite non-negative number.\n");
        return EXIT_FAILURE;
    }

    dog_years = calculate_dog_years(human_years);

    if (!isfinite(dog_years)) {
        fprintf(stderr, "Calculated age is out of range.\n");
        return EXIT_FAILURE;
    }

    printf("%.2f human years is %.2f dog years.\n", human_years, dog_years);
    return EXIT_SUCCESS;
}
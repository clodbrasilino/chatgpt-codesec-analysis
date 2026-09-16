#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_dog_years(int human_years, int *dog_years)
{
    if (dog_years == NULL || human_years < 0) {
        return -1;
    }

    if (human_years <= 2) {
        *dog_years = human_years * 10;
        return 0;
    }

    if (human_years > 2 + (INT_MAX - 20) / 7) {
        return -1;
    }

    *dog_years = 20 + (human_years - 2) * 7;
    return 0;
}

int main(int argc, const char *const argv[])
{
    char *end;
    long input_years;
    int dog_years;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative human years>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input_years = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input_years < 0 || input_years > INT_MAX) {
        fputs("Invalid age.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_dog_years((int)input_years, &dog_years) != 0) {
        fputs("Unable to calculate dog years.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%ld human years is %d dog years.\n", input_years, dog_years);
    return EXIT_SUCCESS;
}
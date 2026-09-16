#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_dog_years(int human_years)
{
    return human_years <= 2
        ? human_years * 10
        : 20 + (human_years - 2) * 7;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    long human_years;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <human_years>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    human_years = strtol(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        human_years < 0 || human_years > 1000) {
        fprintf(stderr, "Invalid age: enter an integer from 0 to 1000.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", calculate_dog_years((int)human_years));

    return EXIT_SUCCESS;
}
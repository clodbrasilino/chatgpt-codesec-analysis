#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 0) {
        return human_years < 0 ? -1 : 0;
    }
    int dog_years = 0;
    dog_years += 15;
    if (human_years >= 2) {
        dog_years += 9;
    }
    if (human_years >= 3) {
        dog_years += (human_years - 2) * 5;
    }
    return dog_years;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        printf("Usage: %s <human_years>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        printf("Invalid input: must be a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }
    int human_years = (int)val;
    int result = calculate_dog_years(human_years);
    if (result == -1) {
        printf("Calculation error: invalid age.\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
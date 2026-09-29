#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INPUT_BUFFER_SIZE 128

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t len;
    size_t input_max;

    input_max = sizeof(input) - 1;

    printf("Enter length of first diagonal: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    /* Possible weaknesses found:
     *  Assuming that condition 'input[len-1]!='\n'' is not redundant
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || len > input_max || input[len - 1] != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'input[len-1]=='\n'' is always true [knownConditionTrueFalse]
     *  Condition 'input[len-1]=='\n'' is always true
     *  Condition 'len>=1' is always true [knownConditionTrueFalse]
     *  Condition 'len>=1' is always true
     */
    if (len >= 1 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d1 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    /* Possible weaknesses found:
     *  Assuming that condition 'input[len-1]!='\n'' is not redundant
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || len > input_max || input[len - 1] != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'input[len-1]=='\n'' is always true [knownConditionTrueFalse]
     *  Condition 'input[len-1]=='\n'' is always true
     *  Condition 'len>=1' is always true [knownConditionTrueFalse]
     *  Condition 'len>=1' is always true
     */
    if (len >= 1 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d2 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    if (area < 0) {
        fprintf(stderr, "Diagonals must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Area of rhombus: %.2f\n", area);
    return EXIT_SUCCESS;
}
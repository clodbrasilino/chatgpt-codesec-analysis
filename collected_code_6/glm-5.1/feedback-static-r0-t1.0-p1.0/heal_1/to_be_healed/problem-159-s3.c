#include <stdio.h>
#include <stdlib.h>

const char *get_season(int month, int day) {
    /* Possible weaknesses found:
     *  Assuming condition 'day>31' is false
     */
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'day>31' is always false [knownConditionTrueFalse]
     *  Condition 'day>31' is always false
     */
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
        return NULL;
    }

    if (month == 2 && day > 29) {
        return NULL;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return NULL;
    }

    if ((month == 3 && day >= 20) || (month == 4) || (month == 5) || (month == 6 && day <= 20)) {
        return "Spring";
    }

    if ((month == 6 && day >= 21) || (month == 7) || (month == 8) || (month == 9 && day <= 21)) {
        return "Summer";
    }

    if ((month == 9 && day >= 22) || (month == 10) || (month == 11) || (month == 12 && day <= 20)) {
        return "Autumn";
    }

    if ((month == 12 && day >= 21) || (month == 1) || (month == 2) || (month == 3 && day <= 19)) {
        return "Winter";
    }

    return NULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long month_long = strtol(argv[1], &endptr1, 10);
    long day_long = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || month_long < 1 || month_long > 12 || day_long < 1 || day_long > 31) {
        fprintf(stderr, "Invalid input format or out of range\n");
        return EXIT_FAILURE;
    }

    int month = (int)month_long;
    int day = (int)day_long;

    const char *season = get_season(month, day);

    if (season == NULL) {
        fprintf(stderr, "Invalid date\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", season);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SPRING,
    SUMMER,
    AUTUMN,
    WINTER,
    INVALID
} Season;

const char* season_to_string(Season s) {
    switch (s) {
        case SPRING: return "Spring";
        case SUMMER: return "Summer";
        case AUTUMN: return "Autumn";
        case WINTER: return "Winter";
        default: return "Invalid";
    }
}

Season get_season(int month, int day) {
    int max_day;

    if (month < 1 || month > 12 || day < 1) {
        return INVALID;
    }

    switch (month) {
        case 2: max_day = 29; break;
        case 4: case 6: case 9: case 11: max_day = 30; break;
        default: max_day = 31; break;
    }

    if (day > max_day) {
        return INVALID;
    }

    switch (month) {
        case 1: case 2:
            return WINTER;
        case 3:
            return day < 20 ? WINTER : SPRING;
        case 4: case 5:
            return SPRING;
        case 6:
            return day < 21 ? SPRING : SUMMER;
        case 7: case 8:
            return SUMMER;
        case 9:
            return day < 22 ? SUMMER : AUTUMN;
        case 10: case 11:
            return AUTUMN;
        case 12:
            return day < 21 ? AUTUMN : WINTER;
        default:
            return INVALID;
    }
}

void print_season(int month, int day) {
    Season s = get_season(month, day);
    if (s == INVALID) {
        fprintf(stderr, "Invalid date\n");
        return;
    }
    printf("%s\n", season_to_string(s));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    long m = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || m < 1 || m > 12) {
        fprintf(stderr, "Invalid month\n");
        return EXIT_FAILURE;
    }

    char *endptr2;
    long d = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || d < 1 || d > 31) {
        fprintf(stderr, "Invalid day\n");
        return EXIT_FAILURE;
    }

    print_season((int)m, (int)d);

    return EXIT_SUCCESS;
}
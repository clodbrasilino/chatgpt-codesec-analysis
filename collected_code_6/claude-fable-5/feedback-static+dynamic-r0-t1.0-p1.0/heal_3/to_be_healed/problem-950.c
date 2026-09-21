#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define ZODIAC_COUNT 12
#define MIN_YEAR 1
#define MAX_YEAR 9999
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Dog', got <no output>
  *  test case 1 failed: expected 'Tiger', got <no output>
  *  test case 0 failed: expected 'Ox', got <no output>
  */

static const char *get_chinese_zodiac(int year)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const signs[ZODIAC_COUNT] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index;

    index = year % ZODIAC_COUNT;
    if (index < 0) {
        index += ZODIAC_COUNT;
    }
    if (index < 0 || index >= ZODIAC_COUNT) {
        return NULL;
    }
    return signs[index];
}

static int display_zodiac(int year)
{
    const char *sign;

    if (year < MIN_YEAR || year > MAX_YEAR) {
        fprintf(stderr, "Error: year must be between %d and %d.\n", MIN_YEAR, MAX_YEAR);
        return -1;
    }
    sign = get_chinese_zodiac(year);
    if (sign == NULL) {
        fprintf(stderr, "Error: could not determine zodiac sign.\n");
        return -1;
    }
    if (printf("%s\n", sign) < 0) {
        return -1;
    }
    if (fflush(stdout) != 0) {
        return -1;
    }
    return 0;
}

static int parse_year(const char *text, int *out_year)
{
    char *endptr;
    long value;

    if (text == NULL || out_year == NULL) {
        return -1;
    }
    errno = 0;
    value = strtol(text, &endptr, 10);
    if (errno != 0 || endptr == text || *endptr != '\0') {
        return -1;
    }
    if (value < INT_MIN || value > INT_MAX) {
        return -1;
    }
    *out_year = (int)value;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int year;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    if (argc > 1) {
        if (parse_year(argv[1], &year) != 0) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    } else {
        result = scanf("%d", &year);
        if (result != 1) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }
    if (display_zodiac(year) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
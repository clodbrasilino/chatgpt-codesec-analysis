#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define ZODIAC_COUNT 12
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Dog', got <no output>
  *  test case 1 failed: expected 'Tiger', got <no output>
  *  test case 0 failed: expected 'Ox', got <no output>
  */

static const char *chinese_zodiac(int year)
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
        return "Unknown";
    }
    return signs[index];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int year;
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    long value;
    char *endptr;

    if (argc > 1) {
        errno = 0;
        endptr = NULL;
        value = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || *endptr != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
        year = (int)value;
    } else {
        if (scanf("%d", &year) != 1) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}
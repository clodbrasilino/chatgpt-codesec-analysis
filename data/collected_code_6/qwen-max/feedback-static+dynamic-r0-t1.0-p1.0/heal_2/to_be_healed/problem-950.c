#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Tiger', got <no output>
  *  test case 0 failed: expected 'Ox', got <no output>
  *  test case 2 failed: expected 'Dog', got <no output>
  */

char *get_chinese_zodiac(int year) {
    const char *zodiac[] = {"Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat"};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    return (const char *)zodiac[(year - 4) % 12];
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int year;
    if (sscanf(argv[1], "%d", &year) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid year.\n");
        return EXIT_FAILURE;
    }

    printf("Chinese Zodiac for the year %d is: %s\n", year, get_chinese_zodiac(year));
    
    return EXIT_SUCCESS;
}
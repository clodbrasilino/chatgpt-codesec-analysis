#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Tiger', got <no output>
  *  test case 0 failed: expected 'Ox', got <no output>
  *  test case 2 failed: expected 'Dog', got <no output>
  */

char *get_chinese_zodiac(int year) {
    static const char *zodiac[] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"};
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
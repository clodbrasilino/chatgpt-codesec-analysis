#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  'get_chinese_zodiac' declared here
 */
char *get_chinese_zodiac(int year) {
    static const char *zodiac[] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"};
    return zodiac[(year - 4) % 12];
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

    /* Possible weaknesses found:
     *  call to undeclared function 'get_chician_zodiac'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'get_chinese_zodiac'?
     *  implicit declaration of function 'get_chician_zodiac'; did you mean 'get_chinese_zodiac'? [-Wimplicit-function-declaration]
     */
    printf("Chinese Zodiac for the year %d is: %s\n", year, get_chician_zodiac(year));

    return EXIT_SUCCESS;
}
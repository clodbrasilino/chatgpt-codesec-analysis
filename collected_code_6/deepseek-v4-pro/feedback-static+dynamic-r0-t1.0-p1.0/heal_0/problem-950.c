#include <stdio.h>

const char* chinese_zodiac_sign(int year) {
    const char *signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index = year % 12;
    if (index < 0) index += 12;
    return signs[index];
}

int main(void) {
    int year;
    printf("Enter a year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("%s\n", chinese_zodiac_sign(year));
    return 0;
}
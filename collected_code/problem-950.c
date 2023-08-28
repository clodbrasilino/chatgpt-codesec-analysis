#include <stdio.h>

void displayChineseZodiacSign(int year) {
    int sign = year % 12;
    switch (sign) {
        case 0:
            printf("Monkey\n");
            break;
        case 1:
            printf("Rooster\n");
            break;
        case 2:
            printf("Dog\n");
            break;
        case 3:
            printf("Pig\n");
            break;
        case 4:
            printf("Rat\n");
            break;
        case 5:
            printf("Ox\n");
            break;
        case 6:
            printf("Tiger\n");
            break;
        case 7:
            printf("Rabbit\n");
            break;
        case 8:
            printf("Dragon\n");
            break;
        case 9:
            printf("Snake\n");
            break;
        case 10:
            printf("Horse\n");
            break;
        case 11:
            printf("Sheep\n");
            break;
        default:
            printf("Invalid year\n");
    }
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    displayChineseZodiacSign(year);
    return 0;
}
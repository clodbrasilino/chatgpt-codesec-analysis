#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has31Days(const char *month) {
    const char *months_with_31[] = {"January", "March", "May", "July", "August", "October", "December"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(months_with_31[i], month) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    char month[20];
    printf("Enter the name of the month: ");
    scanf("%19s", month);  // Limit input to 19 characters to avoid buffer overflow

    if (has31Days(month)) {
        printf("%s has 31 days.\n", month);
    } else {
        printf("%s does not have 31 days.\n", month);
    }

    return 0;
}
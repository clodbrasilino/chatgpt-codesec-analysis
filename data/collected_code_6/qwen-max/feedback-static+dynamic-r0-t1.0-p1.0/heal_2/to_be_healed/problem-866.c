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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[20];
    printf("Enter the name of the month: ");
    fgets(month, sizeof(month), stdin);
    month[strcspn(month, "\n")] = 0;

    if (has31Days(month)) {
        printf("%s has 31 days.\n", month);
    } else {
        printf("%s does not have 31 days.\n", month);
    }

    return 0;
}
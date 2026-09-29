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
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strcspn(month, "\n");
        if (len > 0 && len < sizeof(month) - 1) {
            month[len] = '\0';
            if (has31Days(month)) {
                printf("%s has 31 days.\n", month);
            } else {
                printf("%s does not have 31 days.\n", month);
            }
        } else {
            printf("Invalid input.\n");
            return 1;
        }
    } else {
        printf("Failed to read input.\n");
        return 1;
    }
    return 0;
}
#include <stdio.h>
#include <string.h>

int is_28_days_month(const char *month) {
    if (strcmp(month, "February") == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; ++i) {
        if (is_28_days_month(months[i])) {
            printf("%s has 28 days.\n", months[i]);
        } else {
            printf("%s does not have 28 days.\n", months[i]);
        }
    }
    return 0;
}
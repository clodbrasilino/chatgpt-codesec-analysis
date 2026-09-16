#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool hasThirtyDays(const char *month) {
    if (strcmp(month, "April") == 0 || 
        strcmp(month, "June") == 0 || 
        strcmp(month, "September") == 0 || 
        strcmp(month, "November") == 0) {
        return true;
    }
    return false;
}

int main() {
    const char *test_months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int num_months = sizeof(test_months) / sizeof(test_months[0]);

    for (int i = 0; i < num_months; ++i) {
        if (hasThirtyDays(test_months[i])) {
            printf("%s has 30 days\n", test_months[i]);
        } else {
            printf("%s does not have 30 days\n", test_months[i]);
        }
    }

    return 0;
}
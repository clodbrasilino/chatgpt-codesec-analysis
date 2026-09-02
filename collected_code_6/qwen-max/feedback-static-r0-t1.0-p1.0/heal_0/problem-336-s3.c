#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_month_with_28_days(const char *month_name) {
    if (strcmp(month_name, "February") == 0) {
        return true;
    }
    return false;
}

int main() {
    const char *test_months[] = {"January", "February", "March", "April",
                                 "May", "June", "July", "August",
                                 "September", "October", "November", "December"};
    for (int i = 0; i < 12; ++i) {
        if (is_month_with_28_days(test_months[i])) {
            printf("%s has 28 days.\n", test_months[i]);
        } else {
            printf("%s does not have 28 days.\n", test_months[i]);
        }
    }
    return 0;
}
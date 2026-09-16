#include <stdio.h>
#include <string.h>

int has_31_days(const char *month) {
    if (strcmp(month, "January") == 0 || strcmp(month, "March") == 0 ||
        strcmp(month, "May") == 0 || strcmp(month, "July") == 0 ||
        strcmp(month, "August") == 0 || strcmp(month, "October") == 0 ||
        strcmp(month, "December") == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *months[] = {"January", "February", "March", "April", 
                            "May", "June", "July", "August",
                            "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        if (has_31_days(months[i])) {
            printf("%s has 31 days\n", months[i]);
        } else {
            printf("%s does not have 31 days\n", months[i]);
        }
    }
    return 0;
}
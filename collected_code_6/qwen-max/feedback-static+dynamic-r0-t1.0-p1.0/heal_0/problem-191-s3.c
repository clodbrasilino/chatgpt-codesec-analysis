#include <stdio.h>
#include <string.h>

int hasThirtyDays(const char *month) {
    if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 ||
        strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; ++i) {
        printf("%s: %s\n", months[i], hasThirtyDays(months[i]) ? "30 days" : "Not 30 days");
    }
    return 0;
}
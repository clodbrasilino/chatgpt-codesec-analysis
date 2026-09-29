#include <stdio.h>
#include <string.h>

int has_30_days(char *month_name) {
    const char *months_with_30_days[] = {"April", "June", "September", "November"};
    int i;

    for (i = 0; i < 4; i++) {
        if (strcmp(months_with_30_days[i], month_name) == 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    char month_name[20];

    printf("Enter a month name: ");
    scanf("%s", month_name);

    if (has_30_days(month_name)) {
        printf("%s has 30 days.\n", month_name);
    } else {
        printf("%s does not have 30 days.\n", month_name);
    }

    return 0;
}
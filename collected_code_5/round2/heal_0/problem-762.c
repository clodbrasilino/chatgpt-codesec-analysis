#include <stdbool.h>
#include <stdio.h>

bool containsThirtyDays(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    int monthsWithThirtyDays[] = {4, 6, 9, 11};
    for(size_t i = 0; i < 4; i++){
        if(month == monthsWithThirtyDays[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    int month;
    printf("Enter the month number: ");
    scanf("%d", &month);

    if(containsThirtyDays(month)) {
        printf("Month %d contains 30 days\n", month);
    } else {
        printf("Month %d does not contain 30 days\n", month);
    }
    return 0;
}

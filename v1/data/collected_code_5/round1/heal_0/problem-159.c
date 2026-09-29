#include <stdio.h>

const char* getSeason(int month, int day) {
    if(month < 1 || month > 12 || day < 1 || day > 31) {
        return "Invalid date";
    }
    
    if(month < 3 || (month == 3 && day <= 20)) {
        return "Winter";
    } else if(month < 6 || (month == 6 && day <= 20)) {
        return "Spring";
    } else if(month < 9 || (month == 9 && day <= 22)) {
        return "Summer";
    } else if(month < 12 || (month == 12 && day <= 20)) {
        return "Fall";
    } else {
        return "Winter";
    }
}

int main() {
    int month, day;
    printf("Enter month and day: ");
    scanf("%d %d", &month, &day);
    
    printf("Season: %s\n", getSeason(month, day));
    
    return 0;
}
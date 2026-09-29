#include <stdio.h>
#include <stdbool.h>

bool has_30_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return true;
        default:
            return false;
    }
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }
    
    int month;
    if (sscanf(argv[1], "%d", &month) != 1) {
        fprintf(stderr, "Invalid input: not an integer\n");
        return 1;
    }
    
    if (has_30_days(month)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return true;
        default:
            return false;
    }
}

int main(int argc, char * const argv[const]) {
    int month;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }
    if (sscanf(argv[1], "%d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (has_31_days(month)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}
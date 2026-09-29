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

int main(void) {
    int m;
    
    if (scanf("%d", &m) == 1) {
        if (has_30_days(m)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    } else {
        printf("0\n");
    }
    
    return 0;
}
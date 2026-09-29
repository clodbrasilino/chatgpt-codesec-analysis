#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int angle1, int angle2, int angle3) {
    if (angle1 <= 0 || angle2 <= 0 || angle3 <= 0) {
        return false;
    }
    
    if (angle1 >= 180 || angle2 >= 180 || angle3 >= 180) {
        return false;
    }
    
    if (angle1 + angle2 + angle3 == 180) {
        return true;
    }
    
    return false;
}

int main(void) {
    int a, b, c;

    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("Valid triangle.\n");
        } else {
            printf("Invalid triangle.\n");
        }
    }

    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("Valid triangle.\n");
        } else {
            printf("Invalid triangle.\n");
        }
    }
    
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    int angle1 = atoi(argv[1]);
    int angle2 = atoi(argv[2]);
    int angle3 = atoi(argv[3]);
    
    if (is_valid_triangle(angle1, angle2, angle3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}
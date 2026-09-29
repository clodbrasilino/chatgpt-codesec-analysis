#include <stdio.h>
#include <stdlib.h>

int find_third_angle(int angle1, int angle2, int *third_angle) {
    if (third_angle == NULL) {
        return -1;
    }
    
    if (angle1 <= 0 || angle2 <= 0) {
        return -1;
    }
    
    if ((angle1 + angle2) >= 180) {
        return -1;
    }
    
    *third_angle = 180 - (angle1 + angle2);
    
    return 0;
}

int main(void) {
    int angle1 = 60;
    int angle2 = 45;
    int third_angle = 0;
    
    if (find_third_angle(angle1, angle2, &third_angle) == 0) {
        printf("The third angle is: %d\n", third_angle);
    } else {
        fprintf(stderr, "Error: Invalid angles provided.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
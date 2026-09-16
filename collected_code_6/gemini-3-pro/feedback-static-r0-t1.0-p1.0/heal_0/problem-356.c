#include <stdio.h>
#include <stdlib.h>

int find_third_angle(int angle1, int angle2, int *angle3) {
    if (angle3 == NULL) {
        return -1;
    }
    if (angle1 <= 0 || angle2 <= 0 || (angle1 + angle2) >= 180) {
        return -1;
    }
    
    *angle3 = 180 - (angle1 + angle2);
    
    return 0;
}

int main(void) {
    int angle1 = 60;
    int angle2 = 45;
    int angle3 = 0;

    if (find_third_angle(angle1, angle2, &angle3) == 0) {
        printf("%d\n", angle3);
    } else {
        printf("Invalid angles provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
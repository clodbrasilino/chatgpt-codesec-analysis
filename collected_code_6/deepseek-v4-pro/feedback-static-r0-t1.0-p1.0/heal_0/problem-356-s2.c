#include <stdio.h>

int find_third_angle(int angle1, int angle2) {
    return 180 - angle1 - angle2;
}

int main(void) {
    int angle1 = 60;
    int angle2 = 80;
    int angle3 = find_third_angle(angle1, angle2);
    printf("%d\n", angle3);
    return 0;
}
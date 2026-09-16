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
    int angle1 = 60;
    int angle2 = 60;
    int angle3 = 60;
    
    /* Possible weaknesses found:
     *  Condition 'is_valid_triangle(angle1,angle2,angle3)' is always true
     *  Condition 'is_valid_triangle(angle1,angle2,angle3)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_valid_triangle' returns 1
     */
    if (is_valid_triangle(angle1, angle2, angle3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    angle1 = 90;
    angle2 = 90;
    angle3 = 0;
    
    /* Possible weaknesses found:
     *  Condition 'is_valid_triangle(angle1,angle2,angle3)' is always false
     *  Condition 'is_valid_triangle(angle1,angle2,angle3)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_valid_triangle' returns 0
     */
    if (is_valid_triangle(angle1, angle2, angle3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}
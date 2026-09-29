#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

double cylinder_volume(double radius, double height) {
    if (radius <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

int main(void) {
    double radius, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;
    
    printf("Enter radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';
    errno = 0;
    radius = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE || radius == HUGE_VAL || radius == -HUGE_VAL) {
        printf("Error: Invalid radius input.\n");
        return 1;
    }
    
    printf("Enter height: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';
    errno = 0;
    height = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE || height == HUGE_VAL || height == -HUGE_VAL) {
        printf("Error: Invalid height input.\n");
        return 1;
    }
    
    volume = cylinder_volume(radius, height);
    
    if (volume < 0.0) {
        printf("Error: Radius and height must be positive values.\n");
        return 1;
    }
    
    printf("Volume of cylinder: %.2f\n", volume);
    
    return 0;
}
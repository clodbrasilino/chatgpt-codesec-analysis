#include <stdio.h>

float areaOfTrapezium(float base1, float base2, float height) {
    return 0.5f * (base1 + base2) * height;
}

int main() {
    float base1, base2, height;
    
    if (scanf("%f %f %f", &base1, &base2, &height) != 3) {
        return 1;
    }
    
    float area = areaOfTrapezium(base1, base2, height);
    printf("%.0f\n", area);
    
    return 0;
}
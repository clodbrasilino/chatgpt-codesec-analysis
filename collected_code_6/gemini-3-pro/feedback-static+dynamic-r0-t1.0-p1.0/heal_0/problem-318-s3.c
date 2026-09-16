#include <stdio.h>
#include <err.h>
#include <errno.h>

double find_max_volume(double sum_of_sides) {
    double side;
    
    if (sum_of_sides <= 0) {
        return 0.0;
    }
    
    side = sum_of_sides / 12.0;
    
    return side * side * side;
}

int main(void) {
    double sum = 24.0;
    double volume;
    
    volume = find_max_volume(sum);
    
    if (printf("Maximum volume of cuboid with sum of sides %.2f is %.4f\n", sum, volume) < 0) {
        err(1, "printf failed");
    }
    
    return 0;
}
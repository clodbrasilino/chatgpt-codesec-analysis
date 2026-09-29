#include <stdio.h>

double calcPrismVolume(double base, double height, double length) {
    if (base <= 0 || height <= 0 || length <= 0) {
        printf("Error: All dimensions must be positive.\n");
        return -1;
    }
	
	double volume = 0.5 * base * height * length;
	return volume;
}

int main(void) {
	double base, height, length;
	printf("Enter the base of the triangular prism: ");
	scanf("%lf", &base);
	printf("Enter the height of the triangular prism: ");
	scanf("%lf", &height);
	printf("Enter the length of the triangular prism: ");
	scanf("%lf", &length);

	double volume = calcPrismVolume(base, height, length);
	if(volume >= 0) {
		printf("The volume of the triangular prism is: %.2lf\n", volume);
	}

	return 0;
}
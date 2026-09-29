#include <stdio.h>
#include <math.h>

int maxVolume(int S) {
    int a = S / 3;
    int b = (S - a) / 2;
    int c = S - a - b;
    return a * b * c;
}

int main(void) {
    int sumSides;
    printf("Enter sum of sides: ");
    if (scanf("%d", &sumSides) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (sumSides < 3) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    int volume = maxVolume(sumSides);
    printf("Maximum volume: %d\n", volume);
    return 0;
}
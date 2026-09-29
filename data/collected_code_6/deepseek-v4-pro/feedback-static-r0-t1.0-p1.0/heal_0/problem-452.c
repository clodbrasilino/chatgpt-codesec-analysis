#include <stdio.h>

double loss_or_zero(double face_value, double market_value) {
    if (face_value > market_value) {
        return face_value - market_value;
    }
    return 0.0;
}

int main(void) {
    double face_value = 1000.0;
    double market_value = 850.0;
    double loss = loss_or_zero(face_value, market_value);

    if (loss > 0.0) {
        printf("Loss: %.2f\n", loss);
    } else {
        printf("No loss\n");
    }

    return 0;
}
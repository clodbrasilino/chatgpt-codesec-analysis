#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

float findLateralSurfaceArea(float radius, float height) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     */
    float slantHeight = sqrt(radius * radius + height * height);
    float lateralSurfaceArea = 3.14159 * radius * slantHeight;
    return lateralSurfaceArea;
}

int main() {
    float radius, height;
    printf("Enter the radius of the cone: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    printf("Enter the height of the cone: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &height);
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    float lateralSurfaceArea = findLateralSurfaceArea(radius, height);
    printf("Lateral Surface Area of the cone: %.2f\n", lateralSurfaceArea);
    return 0;
}
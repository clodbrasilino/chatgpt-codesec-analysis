/* Possible weaknesses found:
 *  include '<stdio.h>' or provide a declaration of 'printf'
 *  include '<math.h>' or provide a declaration of 'sqrt'
 */
float find_surface_area(float radius, float height) {
    const float PI = 3.14159;
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     */
    float slant_height = sqrt((radius * radius) + (height * height));
    float base_area = PI * (radius * radius);
    float lateral_area = PI * radius * slant_height;
    float surface_area = base_area + lateral_area;
    return surface_area;
}

int main() {
    float radius, height;
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("Enter the radius of the cone: ");
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'scanf'
     *  implicit declaration of function 'scanf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'scanf' [-Wbuiltin-declaration-mismatch]
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
    float area = find_surface_area(radius, height);
    printf("Surface area of the cone: %f\n", area);

    return 0;
}
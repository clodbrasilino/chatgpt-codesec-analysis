#include <stdio.h>
#include <stdbool.h>

static bool is_valid_triangle(int angle1, int angle2, int angle3)
{
    return angle1 > 0 &&
           angle2 > 0 &&
           angle3 > 0 &&
           angle1 + angle2 + angle3 == 180;
}

int main(void)
{
    int angle1;
    int angle2;
    int angle3;

    if (scanf("%d %d %d", &angle1, &angle2, &angle3) != 3) {
        return 1;
    }

    printf("%s\n", is_valid_triangle(angle1, angle2, angle3) ? "Yes" : "No");

    return 0;
}
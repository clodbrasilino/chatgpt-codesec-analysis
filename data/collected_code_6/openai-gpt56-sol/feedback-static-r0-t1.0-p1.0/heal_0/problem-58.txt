#include <stdbool.h>
#include <stdio.h>

static bool have_opposite_signs(int first, int second)
{
    return (first < 0 && second >= 0) || (first >= 0 && second < 0);
}

int main(void)
{
    int first;
    int second;

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(have_opposite_signs(first, second) ? "Opposite signs" : "Same sign");
    return 0;
}
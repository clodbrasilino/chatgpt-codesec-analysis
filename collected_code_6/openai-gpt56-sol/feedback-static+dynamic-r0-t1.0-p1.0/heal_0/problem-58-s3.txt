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
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    (void)printf("%s\n",
                 have_opposite_signs(first, second) ? "true" : "false");

    return 0;
}
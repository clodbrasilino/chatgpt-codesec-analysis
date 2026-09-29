#include <stdio.h>
#include <stddef.h>

static int reverse_up_to(int *array, size_t length, size_t position)
{
    if (array == NULL || length == 0U || position >= length) {
        return -1;
    }

    for (size_t left = 0U, right = position; left < right; ++left, --right) {
        int temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t position = 3U;

    if (reverse_up_to(array, length, position) != 0) {
        (void)fprintf(stderr, "Unable to reverse the array.\n");
        return 1;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%d%s", array[index], index + 1U < length ? " " : "\n") < 0) {
            return 1;
        }
    }

    return 0;
}
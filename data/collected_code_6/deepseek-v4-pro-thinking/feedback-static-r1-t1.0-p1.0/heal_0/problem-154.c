#include <stdio.h>

int extract_elements(const int *matrix, int rows, int cols,
                     const int indices[][2], int index_count, int *output)
{
    if (matrix == NULL || indices == NULL || rows <= 0 || cols <= 0 || index_count < 0) {
        return -1;
    }

    if (index_count == 0) {
        return 0;
    }

    if (output == NULL) {
        return -1;
    }

    for (int i = 0; i < index_count; ++i) {
        int row = indices[i][0];
        int col = indices[i][1];

        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return -1;
        }

        output[i] = matrix[row * cols + col];
    }

    return index_count;
}

int main(void)
{
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const int indices[][2] = {
        {0, 0},
        {1, 1},
        {2, 2}
    };

    int output[3] = {0};
    int count = extract_elements(&matrix[0][0], 3, 3, indices, 3, output);

    if (count < 0) {
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        printf("%d", output[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }

    printf("\n");
    return 0;
}
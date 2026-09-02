#include <stdio.h>
#include <stdbool.h>

bool isMagicSquare(int n, int square[9][9]) {
    int sum = 0;
    for (int i = 0; i < n; ++i) 
        sum += square[0][i];
    
    for (int i = 1; i < n; ++i) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
            colSum += square[j][i];
        }
        if (rowSum != sum || colSum != sum)
            return false;
    }

    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < n; ++i) {
        diag1 += square[i][i];
        diag2 += square[i][n-i-1];
    }
    if (diag1 != sum || diag2 != sum)
        return false;

    return true;
}

void generateOddMagicSquare(int n, int square[9][9]) {
    int num = 1;
    int i = n/2;
    int j = n-1;
    while (num <= (n*n)) {
        if (i == -1 && j == n) { 
            i = 0;
            j = n-2;
        }
        if (j == n) 
            j = 0;
        if (i < 0) 
            i = n-1;
        if (square[i][j]) {
            j -= 2;
            i++;
            continue;
        }
        else
            square[i][j] = num++; 
        j++;
        i--;
    }
}

int main() {
    int n;
    printf("Enter an odd number (1-9): ");
    scanf("%d", &n);
    if (n < 1 || n > 9 || n % 2 == 0) {
        printf("Please enter a valid odd number between 1 and 9.\n");
        return 1;
    }
    int square[9][9] = {0};

    generateOddMagicSquare(n, square);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }

    if (isMagicSquare(n, square))
        printf("It is a Magic Square.\n");
    else
        printf("It is not a Magic Square.\n");

    return 0;
}
#include <stdio.h>

double calculateProfit(double cost, double sales) {
    if(sales >= 0 && cost >= 0){
        double profit = sales - cost;
        return (profit < 0) ? 0 : profit;
    }
    else {
        printf("Error: Both cost and sales should be non-negative numbers.\n");
        return -1;
    }
}

int main() {
    double cost = 300;
    double sales = 500;
    double profit = calculateProfit(cost, sales);
    if(profit >= 0)
        printf("Profit is %.2f \n", profit);
    else
        printf("No profit.\n");
    return 0;
}
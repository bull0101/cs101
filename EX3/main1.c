#include <stdio.h>

int combination(int n, int r) {
    if (r > n - r) r = n - r; 
    int result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

void printPascal5() {
    int rows = 5;
    for (int i = 0; i < rows; i++) {
        // 對齊用空格
        for (int s = 0; s < rows - i - 1; s++) {
            printf("  ");
        }
        // 輸出數字
        for (int j = 0; j <= i; j++) {
            printf("%4d", combination(i, j));
        }
        printf("\n");
    }
}

int main() {
    printPascal5();  // 直接印出五行
    return 0;
}


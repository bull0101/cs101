#include <stdio.h>
int main() {
    for (int i = 1; i <= 81; i++) {
        int y = (i - 1) / 9 + 1;   // 決定第幾列
        int x = (i - 1) % 9 + 1;   // 決定第幾行
        printf("%d*%d=%d ", y, x, y * x);
        if (x == 9) printf("\n");  // 每 9 個換行
    }
    return 0;
}

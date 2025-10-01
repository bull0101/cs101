#include <stdio.h>
#include <math.h>

int main() {
    double pi = 0.0;
    int n, sign = 1;  // sign控制正負號
    double target = 3.14159;

    for (n = 0; ; n++) {
        // Gregory-Leibniz 第 n 項
        double term = 4.0 / (2 * n + 1) * sign;
        pi += term;

        // 檢查收斂 (精確到小數點後五位)
        if (fabs(pi - target) < 0.000005) {
            break;
        }

        // 切換符號
        sign = -sign;
    }

    printf("x = %d\n", n+1);

    return 0;
}

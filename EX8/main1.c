#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// =================================================================
// 函式：檢查中獎 (已修正邏輯：包含任意一個就算中獎)
// =================================================================

/**
 * @brief 檢查一組樂透號碼是否包含您輸入的 3 個中獎號碼中的任意一個，只要有 1 個匹配就算中獎。
 * @param lotto_nums 樂透號碼陣列 (7個號碼)
 * @param win_nums 中獎號碼陣列 (3個號碼)
 * @param lotto_size 樂透號碼數量 (7)
 * @param win_size 中獎號碼數量 (3)
 * @return true: 至少包含一個中獎號碼
 * @return false: 沒有包含任何中獎號碼
 */
bool check_winning(int lotto_nums[], int win_nums[], int lotto_size, int win_size) {
    // 遍歷三個中獎號碼
    for (int i = 0; i < win_size; i++) {
        // 檢查當前中獎號碼是否在樂透號碼中
        for (int j = 0; j < lotto_size; j++) {
            if (win_nums[i] == lotto_nums[j]) {
                // *** 核心修正：只要找到一個匹配，立刻返回 true ***
                return true; 
            }
        }
    }
    // 遍歷完所有中獎號碼，都沒有找到匹配
    return false;
}

// =================================================================
// 函式：執行兌獎流程 (要求一功能)
// =================================================================
void check_lotto_results() {
    int win_num[3];
    int lotto_num[7];
    char buffer[256];
    int line_index;
    
    printf("\n====================================\n");
    printf("長庚樂透兌獎功能：\n");
    printf("請輸入中獎號碼三個：");
    
    // 讀取三個中獎號碼
    if (scanf("%d %d %d", &win_num[0], &win_num[1], &win_num[2]) != 3) {
        fprintf(stderr, "\n輸入格式錯誤！兌獎結束。\n");
        return;
    }

    // 讀取完三個數字後，清除輸入緩衝區
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("輸入中獎號碼為：%02d %02d %02d\n", win_num[0], win_num[1], win_num[2]);
    printf("以下為中獎彩卷：\n");

    // 2. 開啟並讀取 lotto.txt
    FILE *fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        perror("無法開啟 lotto.txt 檔案");
        return;
    }

    // 讀取檔案直到結束
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // 忽略檔頭和檔尾 (例如：========= lotto649 =========)
        if (buffer[0] != '[') {
            continue;
        }

        // 嘗試解析行索引和樂透號碼
        if (sscanf(buffer, "[%d]: %d %d %d %d %d %d %d", 
                   &line_index, 
                   &lotto_num[0], &lotto_num[1], &lotto_num[2], 
                   &lotto_num[3], &lotto_num[4], &lotto_num[5], &lotto_num[6]) == 8) {
            
            // 3. 判斷是否中獎 (使用新的中獎規則)
            if (check_winning(lotto_num, win_num, 7, 3)) {
                // 4. 輸出中獎彩券
                printf("售出時間：March 13 2025: [%d]:", line_index);
                for (int k = 0; k < 7; k++) {
                    printf(" %02d", lotto_num[k]);
                }
                printf("\n");
            }
        } 
    }

    fclose(fp);
    printf("====================================\n");
}

// =================================================================
// 主程式 (整合 HW3 生成邏輯 + 緩衝區清除 + 兌獎邏輯)
// =================================================================
int main() {
    int N;

    // --- HW3 部分：彩券生成 ---
    printf("請輸入要產生彩券的張數 (N)：");
    if (scanf("%d", &N) != 1 || N < 0 || N > 5) {
        fprintf(stderr, "N 輸入無效或超出範圍 (0-5)。\n");
        return 1;
    }
    
    // 清除輸入緩衝區的殘留換行符 (\n)
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    // 根據題目要求設定隨機數種子
    srand(1);

    int lotto_num[7];
    int new_num;
    
    FILE *fp;
    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        perror("無法建立 lotto.txt 檔案");
        return 1;
    }

    fprintf(fp, "========= lotto649 =========\n");

    // 生成與寫入 lotto.txt 的邏輯
    for (int line_num = 1; line_num <= 5; line_num++) {
        if (line_num <= N) {
            // 生成樂透號碼 (不重複)
            for (int i = 0; i < 7; i++) {
                bool is_repeated;
                do {
                    new_num = rand() % 69 + 1;
                    is_repeated = false;
                    for (int j = 0; j < i; j++) {
                        if (new_num == lotto_num[j]) {
                            is_repeated = true;
                            break;
                        }
                    }
                } while (is_repeated);
                lotto_num[i] = new_num;
            }

            // 輸出樂透號碼到檔案
            fprintf(fp, "[%d]:", line_num);
            for (int k = 0; k < 7; k++) {
                fprintf(fp, " %02d", lotto_num[k]);
            }
            fprintf(fp, "\n");

        } else {
            // 輸出未購買的彩券行
            fprintf(fp, "[%d]: __ __ __ __ __ __ __\n", line_num);
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);


    // --- 要求一/兌獎部分：執行兌獎功能 ---
    check_lotto_results();

    return 0;
}

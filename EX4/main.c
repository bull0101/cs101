# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main() {
    FILE *fp;
    int arr1_write[3] = {0, 1, 2};
    char arr2_write[4] = "ABC";   // 包含 '\0'
    float arr3_write[3] = {1.1, 1.2, 1.3};

    int arr1_read[3];
    char arr2_read[4];
    float arr3_read[3];

    // 開啟二進位檔案 (可寫可讀)
    fp = fopen("a.bin", "wb+");
    if (fp == NULL) {
        printf("開啟檔案失敗！\n");
        return 1;
    }

    // ===== 寫入三個陣列 =====
    fwrite(arr1_write, sizeof(arr1_write), 1, fp);
    fwrite(arr2_write, sizeof(arr2_write), 1, fp);
    fwrite(arr3_write, sizeof(arr3_write), 1, fp);

    // 回到檔案開頭
    fseek(fp, 0, SEEK_SET);

    // ===== 讀取三個陣列 =====
    fread(arr1_read, sizeof(arr1_read), 1, fp);
    fread(arr2_read, sizeof(arr2_read), 1, fp);
    fread(arr3_read, sizeof(arr3_read), 1, fp);

    fclose(fp);

    // ===== 輸出結果 =====
    for (int i = 0; i < 3; i++)
        printf("%d ", arr1_read[i]);
    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%c ", arr2_read[i]);
    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%.6f ", arr3_read[i]);
    printf("\n");

    return 0;
}

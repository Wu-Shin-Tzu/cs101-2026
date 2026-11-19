#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SETS 5
#define NUMS 7      /* 每組 7 個數字：前 6 個由小到大，第 7 個為特別號 */
#define MAX_NUM 69

/* 產生一組不重複的七個數字 (01~69) */
void generate(int set[NUMS])
{
    int used[MAX_NUM + 1] = {0};
    int i, j, n, tmp;

    for (i = 0; i < NUMS; i++) {
        do {
            n = rand() % MAX_NUM + 1;
        } while (used[n]);
        used[n] = 1;
        set[i] = n;
    }

    /* 前 6 個數字由小到大排序，第 7 個(特別號)不動 */
    for (i = 0; i < NUMS - 2; i++) {
        for (j = 0; j < NUMS - 2 - i; j++) {
            if (set[j] > set[j + 1]) {
                tmp = set[j];
                set[j] = set[j + 1];
                set[j + 1] = tmp;
            }
        }
    }
}

int main(void)
{
    int n, i, j;
    int lotto[MAX_SETS][NUMS];
    FILE *fp;
    time_t now;
    char *timestr;

    srand((unsigned int)time(NULL));

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);

    while (n < 1 || n > MAX_SETS) {
        printf("請輸入 1 ~ %d 之間的數字：", MAX_SETS);
        scanf("%d", &n);
    }

    for (i = 0; i < n; i++)
        generate(lotto[i]);

    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟 lotto.txt\n");
        return 1;
    }

    now = time(NULL);
    timestr = ctime(&now);          /* 例如 "Wed Mar  2 14:12:47 2022\n" */
    timestr[24] = '\0';             /* 去掉換行 */

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", timestr);

    for (i = 0; i < MAX_SETS; i++) {
        fprintf(fp, "[%d]:", i + 1);
        for (j = 0; j < NUMS; j++) {
            if (i < n)
                fprintf(fp, " %02d", lotto[i][j]);
            else
                fprintf(fp, " --");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "======== csie@CGU ========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

    return 0;
}

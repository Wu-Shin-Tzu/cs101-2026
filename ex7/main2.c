#include <stdio.h>
#include <string.h>

#define NUM_BOOKS 6
#define TITLE_LEN 64

typedef struct Books {
    int id;
    int price;
    char title[TITLE_LEN];
} book_t;

/* 計算所有書籍的總價錢並輸出 */
void total_price(book_t books[], int n)
{
    int i, sum = 0;

    for (i = 0; i < n; i++)
        sum += books[i].price;

    printf("總共價錢：%d\n", sum);
}

/* 輸出書籍資料到螢幕上 */
void list_books(book_t books[], int n)
{
    int i;

    printf("%-4s %-8s %s\n", "Id", "Price", "Title");
    for (i = 0; i < n; i++)
        printf("%-4d %-8d %s\n", books[i].id, books[i].price, books[i].title);
}

int main()
{
    book_t books[NUM_BOOKS] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };
    book_t read_books[NUM_BOOKS];
    FILE *fp;

    /* 將書籍資料(結構)以二進位方式存入 Book.bin */
    fp = fopen("Book.bin", "wb");
    if (fp == NULL) {
        printf("無法開啟 Book.bin\n");
        return 1;
    }
    fwrite(books, sizeof(book_t), NUM_BOOKS, fp);
    fclose(fp);

    /* 從 Book.bin 讀回來，確認檔案內容正確 */
    fp = fopen("Book.bin", "rb");
    if (fp == NULL) {
        printf("無法讀取 Book.bin\n");
        return 1;
    }
    fread(read_books, sizeof(book_t), NUM_BOOKS, fp);
    fclose(fp);

    list_books(read_books, NUM_BOOKS);
    total_price(read_books, NUM_BOOKS);

    return 0;
}

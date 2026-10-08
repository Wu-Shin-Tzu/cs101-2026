#include <stdio.h>

int main()
{
    int i = 2100;
    if(i%400 == 0 || (i%4 == 0 && i%100 != 0)){
        printf("閨年");
    }
    else{
        printf("不是閨年");
    }
    return 0;
}

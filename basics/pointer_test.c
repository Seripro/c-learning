#include <stdio.h>

int main(void) {
    // 1. 普通の変数（データを直接入れる箱）
    int data = 100;
    
    // 2. ポインタ変数（住所を入れるための箱）
    // 「&data」で dataの住所を取得し、「*p」という住所専用の箱に格納する
    int *p = &data;

    // 3. 結果の表示
    printf("データの中身: %d\n", data);
    
    // 住所を表示するときは %p という特別なフォーマットを使う
    printf("データの住所: %p\n", p);

    return 0;
}
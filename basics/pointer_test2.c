#include <stdio.h>

int main(void) {
    int data = 100;    // 普通の変数
    int *p = &data;    // ポインタ変数 p に、dataの住所(&data)を記憶させる

    printf("変更前 data の中身: %d\n", data);

    // ★ここがHPCの要！
    // dataという名前は一切使わず、住所(p)を経由して中身(*p)を書き換える！
    *p = 999;

    // dataの中身はどうなっているか？
    printf("変更後 data の中身: %d\n", data);

    return 0;
}
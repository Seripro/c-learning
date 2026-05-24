#include <stdio.h>
#include <omp.h>

int main(void) {
    // 全員で共有する「1つの貯金箱」
    long long total_sum = 0;

    // 10万回、1を足す（本来なら答えは 100000 になるはず）
    int N = 100000;

    printf("10万回の足し算を【全コア並列】で実行します...\n");

    // 全コアに分割して一斉に足し算させる
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < N; i++) {
        // ★ここが危険地帯！全員が同じ total_sum に同時にアクセスする！
        total_sum = total_sum + 1;
    }

    printf("計算結果: %lld (期待値: 100000)\n", total_sum);

    return 0;
}
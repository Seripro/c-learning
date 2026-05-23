#include <stdio.h>
#include <omp.h>  // OpenMPの機能を使うための設計図

int main(void) {
    // ここから下のブロック（{}の中）を、CPUの全力（全スレッド）で並列実行しろ！という強力な魔法の呪文
    #pragma omp parallel
    {
        // 自分が今、何番目のスレッド（作業員）なのかを取得する
        int thread_id = omp_get_thread_num();
        
        printf("Hello from thread %d!\n", thread_id);
    }
    return 0;
}

// コンパイル方法
// gcc-15 -Wall -fopenmp omp_hello.c -o omp_hello
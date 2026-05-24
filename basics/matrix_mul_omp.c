#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // ★追加：OpenMPの設計図

int main(void) {
    int N = 1024;
    printf("サイズ %d x %d の行列積を【OpenMP全コア】で計算します...\n", N, N);

    double *A = (double*)malloc(sizeof(double) * N * N);
    double *B = (double*)malloc(sizeof(double) * N * N);
    double *C = (double*)malloc(sizeof(double) * N * N);

    if (A == NULL || B == NULL || C == NULL) {
        printf("メモリ確保失敗\n");
        return 1;
    }

    // 1. 初期化
    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    // ★変更：HPCの絶対ルール！現実時間を測る！
    double start_time = omp_get_wtime();

    // ★追加：これが魔法の呪文だ！「直後の for ループを全コアで分割して走らせろ！」
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    // ★変更：計測終了
    double end_time = omp_get_wtime();

    // 3. 結果の表示
    printf("C[0] の結果: %f\n", C[0]);
    // ★変更：時間の計算方法もシンプルになる
    printf("行列積 (OpenMP全コア) の計算時間: %f 秒\n", end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
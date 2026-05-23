#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int N = 1024; // 1024 × 1024 の行列
    printf("サイズ %d x %d の行列積の計算を開始します...\n", N, N);

    // ★HPCの重要テクニック：2次元配列(行列)を、1次元の長い配列として確保する！
    // なぜか？メモリの「連続した広大な倉庫」を一気に借りる方が、圧倒的に処理が速いからだ。
    double *A = (double*)malloc(sizeof(double) * N * N);
    double *B = (double*)malloc(sizeof(double) * N * N);
    double *C = (double*)malloc(sizeof(double) * N * N);

    if (A == NULL || B == NULL || C == NULL) {
        printf("メモリ確保失敗\n");
        return 1;
    }

    // 1. 準備（初期化）
    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    clock_t start_time = clock();

    // 2. メインの計算：C = A × B （約10億回の計算！）
    // 3重ループ。これがCPUを極限までいじめる「HPCの基本形」だ。
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // [i][j] などの2次元の座標を、1次元の住所に変換する計算式が i * N + j だ。
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    clock_t end_time = clock();

    // 3. 結果と時間の表示
    printf("C[0] の結果: %f\n", C[0]);
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("行列積 (CPU 1コア) の計算時間: %f 秒\n", elapsed);

    // 4. お片付け
    free(A);
    free(B);
    free(C);

    return 0;
}

// 例えば、3 × 3 （N=3）の行列を考えてみてくれ。
// [0] [1] [2]  ← 0行目 (i=0)
// [3] [4] [5]  ← 1行目 (i=1)
// [6] [7] [8]  ← 2行目 (i=2)

// これを1列の長い配列にすると、[0, 1, 2, 3, 4, 5, 6, 7, 8] になる。
// では、**「1行目の2列目（本来なら数字の『5』が入っている場所）」**にアクセスしたい時、1次元配列の何番目を見ればいいか？
// 	1.	まず、自分のいる行（i=1）の分だけ、幅（N=3）をスキップして進む。
// i * N ＝ 1 * 3 ＝ 3歩進む （これで次の行の先頭に着く）
// 	2.	そこから、列（j=2）の分だけ右に進む。
// + j ＝ + 2 ＝ さらに2歩進む
// 	3.	合計：3 + 2 = 5 番目！
// つまり、**i * N + j というのは、「2次元の座標を、1次元の住所に翻訳するための魔法の数式」**なんだ。
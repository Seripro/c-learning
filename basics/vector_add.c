#include <stdio.h>
#include <stdlib.h>
#include <time.h> // ★時間を計測するための新しい設計図

int main(void) {
    // データ数：1億個（HPCではこれくらいの規模は当たり前だ！）
    long long N = 100000000; 
    
    // 物理シミュレーションでは精度が命。整数の int ではなく、
    // 実数（小数）を扱える double（倍精度浮動小数点数）を使うのが世界の常識だ。
    printf("1億個の要素を持つベクトルを3つ（約2.4GB）メモリに確保します...\n");
    
    // malloc で巨大な倉庫を3つ借りる
    double *A = (double*)malloc(sizeof(double) * N);
    double *B = (double*)malloc(sizeof(double) * N);
    double *C = (double*)malloc(sizeof(double) * N);

    // エラーチェック（プロのお作法）
    if (A == NULL || B == NULL || C == NULL) {
        printf("メモリの確保に失敗しました！\n");
        return 1;
    }

    // 1. 準備：配列 A と B に適当なデータ（初期値）を入れる
    // ここは計算のメインではないので、時間は気にしない
    for (long long i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    printf("計算を開始します...\n");

    // === ここから時間を計測する ===
    clock_t start_time = clock();

    // 2. メインの計算：C = A + B （1億回の足し算）
    // 現在のコードは、CPUのエリート教授「1人」に1億回足し算をさせている状態だ。
    for (long long i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    // === ここで時間計測終了 ===
    clock_t end_time = clock();

    // 3. 結果の確認（ちゃんと計算できているか、最初の1つだけ確認）
    printf("C[0] の結果: %f (期待値: 3.0)\n", C[0]);

    // 4. かかった時間の計算と表示
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("CPU 1コアでの計算時間: %f 秒\n", elapsed);

    // 5. お片付け（2.4GBもの巨大な倉庫を必ず返す！）
    free(A);
    free(B);
    free(C);

    return 0;
}
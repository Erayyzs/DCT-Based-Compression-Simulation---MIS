#include <stdio.h>
#include <math.h>

#define N 8

void dct(float input[N][N], float output[N][N]) {
    int u, v, x, y;
    float cu, cv, sum;

    for (u = 0; u < N; u++) {
        for (v = 0; v < N; v++) {
            if (u == 0) cu = 1.0 / sqrt(2.0); else cu = 1.0;
            if (v == 0) cv = 1.0 / sqrt(2.0); else cv = 1.0;

            sum = 0.0;
            for (x = 0; x < N; x++) {
                for (y = 0; y < N; y++) {
                    sum += input[x][y] * cos((2 * x + 1) * u * M_PI / (2 * N)) * cos((2 * y + 1) * v * M_PI / (2 * N));
                }
            }
            output[u][v] = 0.25 * cu * cv * sum;
        }
    }
}

void idct(float input[N][N], float output[N][N]) {
    int u, v, x, y;
    float cu, cv, sum;

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            sum = 0.0;
            for (u = 0; u < N; u++) {
                for (v = 0; v < N; v++) {
                    if (u == 0) cu = 1.0 / sqrt(2.0); else cu = 1.0;
                    if (v == 0) cv = 1.0 / sqrt(2.0); else cv = 1.0;

                    sum += cu * cv * input[u][v] * cos((2 * x + 1) * u * M_PI / (2 * N)) * cos((2 * y + 1) * v * M_PI / (2 * N));
                }
            }
            output[x][y] = 0.25 * sum;
        }
    }
}

void apply_mask(float dct[N][N], int mask[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dct[i][j] *= mask[i][j];
        }
    }
}

float calculate_correlation(float matrix[N][N], int block_x, int block_y) {
    float mean_x = 0, mean_y = 0, sum_x = 0, sum_y = 0, sum_xy = 0;
    int count = 0;

    for (int i = block_x; i < block_x + 2; i++) {
        for (int j = block_y; j < block_y + 2; j++) {
            mean_x += matrix[i][j];
            mean_y += matrix[i + 2][j];
            count++;
        }
    }

    mean_x /= count;
    mean_y /= count;

    for (int i = block_x; i < block_x + 2; i++) {
        for (int j = block_y; j < block_y + 2; j++) {
            sum_x += (matrix[i][j] - mean_x) * (matrix[i][j] - mean_x);
            sum_y += (matrix[i + 2][j] - mean_y) * (matrix[i + 2][j] - mean_y);
            sum_xy += (matrix[i][j] - mean_x) * (matrix[i + 2][j] - mean_y);
        }
    }

    return sum_xy / sqrt(sum_x * sum_y);
}

void print_matrix(float matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    float input[N][N] = {
        {168, 161, 161, 150, 154, 168, 164, 154},
        {171, 154, 161, 150, 157, 171, 150, 164},
        {171, 168, 147, 164, 164, 161, 143, 154},
        {164, 171, 154, 161, 157, 157, 147, 132},
        {161, 161, 157, 154, 143, 161, 154, 132},
        {164, 161, 161, 154, 150, 157, 154, 140},
        {161, 168, 157, 154, 161, 140, 140, 132},
        {154, 161, 157, 150, 140, 132, 136, 128}
    };

    int mask[N][N] = {
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    float dct_output[N][N];
    float idct_output[N][N];

    dct(input, dct_output);
    apply_mask(dct_output, mask);
    idct(dct_output, idct_output);

    printf("DCT Output:\n");
    print_matrix(dct_output);

    printf("\nIDCT Output:\n");
    print_matrix(idct_output);

    float correlation_before = calculate_correlation(input, 0, 0);
    float correlation_after = calculate_correlation(idct_output, 0, 0);

    printf("\nCorrelation Before DCT: %f\n", correlation_before);
    printf("Correlation After IDCT: %f\n", correlation_after);

    return 0;
}

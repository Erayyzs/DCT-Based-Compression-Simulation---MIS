# DCT-Based-Compression-Simulation---MIS
This project demonstrates a core step of lossy image compression by applying the Discrete Cosine Transform (DCT) to an 8x8 matrix.

Methodology
The process follows these key steps:

Correlation Analysis (Before): The correlation between specified adjacent blocks in the original 8x8 input matrix was calculated. 

DCT Calculation: A 2D-DCT was performed on the entire 8x8 input matrix. 

Quantization (Masking): The resulting 64 DCT coefficients were filtered using a given mask matrix. This mask effectively discards most of the high-frequency coefficients, keeping only the 10 most significant ones. 
IDCT Reconstruction: A 2D-IDCT was performed on the masked coefficients to reconstruct the matrix. 
Correlation Analysis (After): The correlation was recalculated for the same blocks on the newly reconstructed matrix to observe the effects of the compression. 

Results
The program outputs the calculated DCT coefficients, the reconstructed IDCT matrix, and the correlation values.  The most significant finding is the change in data correlation, which demonstrates the impact of the lossy compression process.

Correlation Before DCT: -0.595570 
Correlation After IDCT: 0.942954 

The final reconstructed matrix  is a close approximation of the original, achieved using only a fraction of the initial data, showcasing the efficiency of DCT in data compression.

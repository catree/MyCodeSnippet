#include <iostream>
#include <cmath>
#include <cstdio>

__global__
void add(int N, float *x, float *y)
{   
    printf("threadIdx.y: %d, threadIdx.z: %d\n", threadIdx.y, threadIdx.z);
    int index = blockDim.x * blockIdx.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = index; i < N; i += stride) { y[i] = x[i] + y[1]; }
}

int main()
{
    int N = 1 << 20;
    float *x, *y;
    
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
        y[i] = 2.0;
    }

    int blockSize = 256;
    int blockNum = (N + blockSize - 1) / blockSize;
    add<<<blockNum, blockSize>>>(N, x, y);

    cudaDeviceSynchronize();

    float max_error = 0.0f;
    for (int i = 0; i < N; i++) {
        max_error = fmax(max_error, y[i] - 3.0f);
    }
    std::cout << "Max Error: " << max_error << std::endl;

    cudaFree(x);
    cudaFree(y);
}
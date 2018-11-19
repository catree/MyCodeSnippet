#include <cstdio>

__global__
void saxpy(int n, float a, float *x, float *y)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < n) y[i] = a * y[i] + x[i];
}

int main()
{
    int n = 1 << 20;

    float *x = new float [n];
    float *y = new float [n];

    for (int i = 0; i < n; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    float *dx, *dy;
    cudaMallocManaged(&dx, n * sizeof(float));
    cudaMallocManaged(&dy, n * sizeof(float));

    cudaMemcpy(dx, x, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dy, y, n * sizeof(float), cudaMemcpyHostToDevice);

    saxpy<<<(n + 255) / 256, 256>>>(n, 2.0f, dx, dy);

    cudaDeviceSynchronize();
    
    cudaMemcpy(y, dy, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Get the error variable and resets it to cudaSuccess
    cudaError_t errSync = cudaGetLastError();

    // Asynchronous error s which occur on the device after control
    // is returned to the host, such as out-of-bounds memory accesses, 
    // require a synchronization mechanism. Any asynchronous eror is
    // returned by cudaDeviceSynchronize().
    cudaError_t errAsync = cudaDeviceSynchronize();
    
    if (errSync != cudaSuccess) { 
        printf("Sync kernel error: %s\n", cudaGetErrorString(errSync)); 
    }
    if (errAsync != cudaSuccess) { 
        printf("Async kernel error: %s\n", cudaGetErrorString(errAsync)); 
    }

    delete [] x;
    delete [] y;
    cudaFree(dx);
    cudaFree(dy);
}
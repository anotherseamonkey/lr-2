#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <format>
#include <omp.h>

using namespace std;

void saveTime(const string name, float* time) {
    ofstream fout(name);
    for (int j = 0; j < 6; j++)
    {
        fout << time[j] << endl;
    }
    fout.close();
}

int main() 
{
   
    clock_t start;

    int arr[6] = {200, 400, 800, 1200, 1600, 2000};
    int l = 0;
    int threads = 16;
    float *time_m;
    time_m = new float[6];
    for (l; l < 6; l++) {
        const int N = arr[l];
        cout << N << endl;
        cout << "Begin initializing ..." << endl;

        float* A, * B;

        // Allocating memory for 2 initial matrices
        A = new float[N * N];
        B = new float[N * N];

        // initializing matrix A and B with random numbers
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                A[i * N + j] = (i + 1) * (j + 1);
                B[i * N + j] = (i + 1) + 2 * (j + 1);
            }

            float* C = new float[N * N];

            cout << "Begin calculating ..." << endl;

            start = clock();
            double wtime = omp_get_wtime();

            // Sequantial matrix multiplication

           #pragma omp parallel for num_threads(threads) shared(A, B, C)
                    for (int i = 0; i < N; i++){
                        for (int j = 0; j < N; j++){
                            C[i * N + j] = 0;
                            for (int k = 0; k < N; k++)
                            {
                                C[i * N + j] += A[i * N + k] * B[k * N + j];
                            }
                        }
                }
            

            wtime = omp_get_wtime() - wtime;
            double time = double(clock() - start) / CLOCKS_PER_SEC;
            cout << "omp time: " << wtime << " seconds" << endl << "number of threads: "<< threads << endl;
            time_m[l] = wtime;

        // free memory
        delete[] A;
        delete[] B;
        delete[] C;

    }
    
    saveTime(format("Time (num of threads = {})", threads), time_m);
    delete[] time_m;

    return 0;
}

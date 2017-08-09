/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <arrayfire.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

using namespace af;

// create a small wrapper to benchmark
static array A; // populated before each timing
static void benchmarkRegions()
{
    array B = regions(A);
    B.eval();
}

int main(int argc, char ** argv)
{
    try {
        int device = argc > 1 ? atoi(argv[1]) : 0;
        setDevice(device);
        info();

        printf("Benchmark regions(Connected-Componenets) on NxN Image\n");
        for (int n = 128; n <= 2048; n += 128) {

            printf("%4d x %4d: ", n, n);
            A = randu(n, n) > 0.5; //b8 input

            printf("Avg. Time Taken:  %g \n", timeit(benchmarkRegions));
            fflush(stdout);
        }
    } catch (af::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }

    return 0;
}

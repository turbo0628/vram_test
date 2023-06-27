#include "vram_stats.hpp"

#include <stdio.h>
#include <cuda.h>

int main() {
    float* pseudo_buffer {nullptr};
    cudaMalloc(&pseudo_buffer, 1<<30);
    size_t vram_usage = VramStats::GetTacoUsage();
    printf("VRAM usage %zu bytes\n", vram_usage);
    cudaFree(pseudo_buffer);
    return 0;
}
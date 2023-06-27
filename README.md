# VRAM test

Build
```
nvcc -std=c++11 vram_stats.cpp -lnvidia-ml test.cu
```

Demostrate how to get GPU mem usage in current process, via NVML.
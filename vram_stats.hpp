#pragma once

#include <nvml.h>
#include <cstddef>


class VramStats {
 public:
  static std::size_t GetTacoUsage();

  VramStats();
  ~VramStats();

  std::size_t GetTotalVram();
  std::size_t GetAvailableVram();

 private:
  std::size_t GetComputeUsage(unsigned int pid);
  std::size_t GetGraphicsUsage(unsigned int pid);

  nvmlDevice_t device_{nullptr};
  unsigned device_id_{0};
};


#include "vram_stats.hpp"

#include <unistd.h>
#include <vector>


unsigned int GetProcessId() {
  return getpid();
}

std::size_t VramStats::GetTacoUsage() {
  unsigned int pid = GetProcessId();
  VramStats stats;
  auto usage = stats.GetGraphicsUsage(pid);
  if (usage > 0) {
    return usage;
  }
  return stats.GetComputeUsage(pid);
}

VramStats::VramStats() {
  nvmlInit();
  nvmlDeviceGetHandleByIndex(device_id_, &device_);
}

VramStats::~VramStats() {
  nvmlShutdown();
}

std::size_t VramStats::GetGraphicsUsage(unsigned int pid) {
  unsigned int graphics_info_count{0};
  std::vector<nvmlProcessInfo_t> graphics_infos;

  nvmlDeviceGetGraphicsRunningProcesses(device_, &graphics_info_count, nullptr);
  graphics_infos.resize(graphics_info_count);
  nvmlDeviceGetGraphicsRunningProcesses(device_, &graphics_info_count,
                                        graphics_infos.data());
  for (std::size_t i = 0; i < graphics_infos.size(); ++i) {
    if (pid == graphics_infos[i].pid) {
      return graphics_infos[i].usedGpuMemory;
    }
  }
  return 0;
}

std::size_t VramStats::GetComputeUsage(unsigned int pid) {
  unsigned int compute_info_count{0};
  std::vector<nvmlProcessInfo_t> compute_infos;

  nvmlDeviceGetComputeRunningProcesses(device_, &compute_info_count, nullptr);
  compute_infos.resize(compute_info_count);
  nvmlDeviceGetComputeRunningProcesses(device_, &compute_info_count,
                                       compute_infos.data());
  for (std::size_t i = 0; i < compute_infos.size(); ++i) {
    if (pid == compute_infos[i].pid) {
      return compute_infos[i].usedGpuMemory;
    }
  }
  return 0;
}

std::size_t VramStats::GetTotalVram() {
  nvmlMemory_t mem_info{};
  nvmlDeviceGetMemoryInfo(device_, &mem_info);
  return mem_info.total;
}

std::size_t VramStats::GetAvailableVram() {
  nvmlMemory_t mem_info{};
  nvmlDeviceGetMemoryInfo(device_, &mem_info);
  return mem_info.free;
}

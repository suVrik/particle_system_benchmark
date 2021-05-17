#pragma once

#include <chrono>

class CpuProfilerStaticScope {
public:
    CpuProfilerStaticScope(const char* name);
    ~CpuProfilerStaticScope();

private:
    const char* m_name;
    long long m_nanoseconds;

    friend class CpuProfilerRuntimeScope;
};

class CpuProfilerRuntimeScope {
public:
    CpuProfilerRuntimeScope(CpuProfilerStaticScope& static_scope);
    ~CpuProfilerRuntimeScope();

private:
    CpuProfilerStaticScope& m_static_scope;
    std::chrono::high_resolution_clock::time_point m_point;
};

#ifdef CPU_PROFILER_ENABLED
#define CPU_PROFILER_SCOPE(name)                        \
static CpuProfilerStaticScope __STATIC_SCOPE(name);     \
CpuProfilerRuntimeScope __RUNTIME_SCOPE(__STATIC_SCOPE)
#else
#define CPU_PROFILER_SCOPE(name) ((void)0)
#endif // CPU_PROFILER_ENABLED

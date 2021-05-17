#include "particle_system/auxiliary/cpu_profiler.h"

#include <iomanip>
#include <iostream>

CpuProfilerStaticScope::CpuProfilerStaticScope(const char* name)
    : m_name(name)
    , m_nanoseconds(0)
{
}

CpuProfilerStaticScope::~CpuProfilerStaticScope() {
    std::cout << std::setw(10) << m_name << ": " << std::setw(10) << m_nanoseconds << std::endl;
}

CpuProfilerRuntimeScope::CpuProfilerRuntimeScope(CpuProfilerStaticScope& static_scope)
    : m_static_scope(static_scope)
    , m_point(std::chrono::high_resolution_clock::now())
{
}

CpuProfilerRuntimeScope::~CpuProfilerRuntimeScope() {
    m_static_scope.m_nanoseconds += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_point).count();
}

// Copyright (c) 2020 Colin Harker

#ifndef MEMORY_H
#define MEMORY_H

#include <string>

#include "utils.h"

class RandomAccessMemory
{
private:
    unsigned long memTotal = 0;
    unsigned long memAvailable = 0;
    unsigned long swapTotal = 0;
    unsigned long swapFree = 0;

    float memUsagePercent = -1.0;
    float swapUsagePercent = -1.0;

    /** parses information from /proc/meminfo
     * @param memInfoType choose from MemTotal, MemAvailable, SwapTotal,
     * SwapFree. Types found in /proc/meminfo
     * @param classVariable specifies which class variable we will modify
     */
    void parseMemInfo(const std::string& memInfoType,
                      flag::memType classVariable);

public:
    /** calls run();
     */
    RandomAccessMemory();

    /** Calls parseMemInfo(); for each class variable
     */
    void run();

    /** Calculates memUsagePercent and swapUsagePercent
     * assigns values to respective class variable
     */
    void calculateMemSwapUsage();

    float getMemUsage() const;
    float getSwapUsage() const;
};

#endif
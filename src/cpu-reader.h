// Copyright (c) 2020 Colin Harker

#ifndef CPU_READER_H
#define CPU_READER_H

#include <vector>
#include <fstream>

class CpuReader
{
private:
    std::string modelName;
    std::string version;

    size_t previousIdleTime = 0;
    size_t previousTotalTime = 0;
    size_t idleTime;
    size_t totalTime;

    float utilization;

    friend class Cpu;

    /** math function to accumulate values provided for total_time variable,
     * from cpu information files
     * @param lineNumberTarget the line in the /proc/stat file we are targeting
     * @return bool for success or failure
     */
    bool getCpuTimes(int lineNumberTarget);

    /** parsing information from /proc/stat
     * @param lineNumberTarget the line in the /proc/stat file we are targeting
     * @return vector of provided information
     */
    std::vector<size_t> retrieveCpuTimes(int) const;

    /**  calculates the total cpu utilization, takes in an int to
     * specify what information to parse. 0 parses total cpu, 1-8
     *  or more denotes specific cores.
     * @param lineNumberTarget the line in the /proc/stat file we are targeting
     */
    void run(int lineNumberTarget);

public:
    void setModelName(const std::string&);
    float getUtilization() const;
};

#endif
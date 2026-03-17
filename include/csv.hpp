#pragma once

#include <vector>
#include <string>

// Write GBM paths to CSV
void write_paths_to_csv(
    const std::string& filename,
    const std::vector<std::vector<double>>& paths,
    double dt
);

#include "csv.hpp"
#include <fstream>
#include <iostream>

void write_paths_to_csv(
    const std::string& filename,
    const std::vector<std::vector<double>>& paths,
    double dt
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    int n_paths = paths.size();
    int steps = paths[0].size();

    // Header
    file << "time";
    for (int i = 0; i < n_paths; i++) {
        file << ",path_" << i;
    }
    file << "\n";

    // Data
    for (int t = 0; t < steps; t++) {
        file << t * dt;
        for (int p = 0; p < n_paths; p++) {
            file << "," << paths[p][t];
        }
        file << "\n";
    }

    file.close();
}

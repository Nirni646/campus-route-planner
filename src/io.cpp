// src/io.cpp
#include "io.hpp"

#include <fstream>
#include <iostream>

CampusMap loadCampusMap(const std::string& filename) {
    CampusMap cmap;

    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error: could not open file " << filename << "\n";
        return cmap;
    }

    int N, M;
    if (!(in >> N >> M)) {
        std::cerr << "Error: invalid file header in " << filename << "\n";
        return cmap;
    }

    cmap.g.resize(N);
    cmap.idToName.resize(N);

    // Read N location names (no spaces; use underscores if needed)
    for (int i = 0; i < N; ++i) {
        std::string name;
        in >> name;
        cmap.idToName[i] = name;
        cmap.nameToId[name] = i;
    }

    // Read M edges: nameU nameV weight
    for (int i = 0; i < M; ++i) {
        std::string uName, vName;
        double w;
        if (!(in >> uName >> vName >> w)) {
            std::cerr << "Warning: failed to read edge " << i << " from file.\n";
            break;
        }
        auto itU = cmap.nameToId.find(uName);
        auto itV = cmap.nameToId.find(vName);
        if (itU == cmap.nameToId.end() || itV == cmap.nameToId.end()) {
            std::cerr << "Warning: unknown location(s) in edge: "
                      << uName << " " << vName << "\n";
            continue;
        }
        cmap.g.addEdge(itU->second, itV->second, w, true);
    }

    return cmap;
}

int getLocationId(const CampusMap& cmap, const std::string& name) {
    auto it = cmap.nameToId.find(name);
    if (it == cmap.nameToId.end()) return -1;
    return it->second;
}

// src/io.hpp
#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "graph.hpp"

struct CampusMap {
    Graph g;
    std::unordered_map<std::string, int> nameToId;
    std::vector<std::string> idToName;
};

// Load campus map from file.
// Expected format:
//   N M
//   name0
//   name1
//   ...
//   nameN-1
//   nameU nameV weight
//   ... (M lines)
CampusMap loadCampusMap(const std::string& filename);

// Get location ID from name, or -1 if not found
int getLocationId(const CampusMap& cmap, const std::string& name);

#endif // IO_HPP

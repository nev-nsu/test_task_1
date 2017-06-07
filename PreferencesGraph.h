#ifndef PREFERENCESGRAPH_H
#define PREFERENCESGRAPH_H


#include <unordered_map>
#include <vector>
#include <set>

class PreferencesGraph {
private:
    std::unordered_map<std::string, size_t> encode;
    std::vector<std::string> decode;
    std::vector<std::set<size_t>> edges;
    std::vector<size_t> likes;
public:
    PreferencesGraph();

    PreferencesGraph(const std::string &file_with_names, const std::string &file_with_preferences);

    void add_human(const std::string &name);

    void add_preference(const std::string &source, const std::string &target);

    std::vector<std::string> get_cute() const;

    std::vector<std::string> get_ugly() const;

    std::vector<std::string> get_unhappy() const;
};


#endif

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "PreferencesGraph.h"

std::vector<std::string> PreferencesGraph::get_cute() const {
    std::vector<std::string> ret(0);
    if (!likes.empty()) {
        size_t max_value = *std::max_element(likes.begin(), likes.end());
        for (auto i = 0; i < likes.size(); i++) {
            if (likes[i] == max_value)
                ret.push_back(decode[i]);
        }
    }
    return ret;
}

std::vector<std::string> PreferencesGraph::get_ugly() const {
    std::vector<std::string> ret(0);
    for (auto i = 0; i < likes.size(); i++) {
        if (likes[i] == 0)
            ret.push_back(decode[i]);
    }
    return ret;
}

std::vector<std::string> PreferencesGraph::get_unhappy() const {
    std::vector<std::string> ret(0);
    for (auto i = 0; i < edges.size(); i++) {
        auto happy = false;
        for (auto j : edges[i]) {
            if (edges[j].find(i) != edges[j].end()) {
                happy = true;
                break;
            }
        }
        if (!happy && !edges[i].empty())
            ret.push_back(decode[i]);
    }
    return ret;
}

void PreferencesGraph::add_human(const std::string &name) {
    encode.emplace(std::make_pair(name, decode.size()));
    decode.push_back(name);
    edges.push_back(std::set<size_t>{});
    likes.push_back(0);
}

void PreferencesGraph::add_preference(const std::string &source, const std::string &target) {
    auto a = encode.find(source);
    auto b = encode.find(target);
    if (a == encode.end() || b == encode.end()) {
        std::cerr << "Name \"" << source << "\" or \"" << target << "\" not found.\n";
    } else {
        edges[a->second].insert(b->second);
        likes[b->second]++;
    }
}

PreferencesGraph::PreferencesGraph(const std::string &file_with_names, const std::string &file_with_preferences) {
    std::ifstream in(file_with_names);
    if (!in) {
        std::cerr << "File \"" << file_with_names << "\" not found." << std::endl;
        std::exit(0);
    }
    do {
        std::string name;
        in >> name;
        if (!name.empty())
            add_human(name);
    } while (in);
    in.close();
    in.open(file_with_preferences);
    if (!in) {
        std::cerr << "File \"" << file_with_preferences << "\" not found. " << std::endl;
        std::exit(0);
    }
    do {
        std::string name1, name2;
        in >> name1 >> name2;
        if (!name1.empty() && !name2.empty())
            add_preference(name1, name2);
    } while (in);

    in.close();
}

PreferencesGraph::PreferencesGraph() {}

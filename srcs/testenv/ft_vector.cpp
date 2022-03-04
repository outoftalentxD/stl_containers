#include <vector>

#include "../vector.hpp"
#include "../pair.hpp"

using namespace ft;

int main() {
    vector<int> vec0;
    size_t testSize = 10000;

    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        int value = rand() % testSize + 1;
        vec0.insert(vec0.begin(), value);
        vec0.insert(vec0.end(), value);
        vec0.insert(vec0.begin() + vec0.size() / 2, 2 * value);
    }
    vector<int> vec1(vec0.begin(), vec0.end());
    vec0.clear();
    vector<pair<std::string, int> > vec2;
    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        int value = rand() % testSize + 1;
        vec2.push_back(make_pair("melaena", value));
        vec2.push_back(make_pair("melaena", value));
        vec2.push_back(make_pair("melaena", value));
        vec2.push_back(make_pair("melaena", value));
        vec2.push_back(make_pair("melaena", value));
        vec2.pop_back();
        vec2.erase(vec2.begin(), vec2.end());
    }
    vector<float> vec3;
    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        vec3.resize(i);
    }
    vector<double> vec4;
    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        vec4.reserve(i);
    }
}

#include <map>

#include "../map.hpp"
#include "../pair.hpp"

using namespace std;

int main() {
    map<int, int> data1;
    size_t testSize = 4000;

    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        int value = rand() % testSize + 1;
        data1.insert(make_pair(value, i));
        data1.insert(make_pair(value + testSize, i));
        data1.insert(make_pair(value + 2 * testSize, i));
        data1[value + testSize] = i;
    }

    map<int, int> data2(data1);
    map<int, int> data3;
    data3.insert(data2.begin(), data2.end());
    for (size_t i = testSize; i < testSize + testSize + testSize; ++i) {
        srand(i);
        int value = rand() % testSize + 1;
        data2.count(value);
        data2.count(value);
        data2.count(value);
        data2.count(value);
        int temp = data2[value];
        data2[value] = temp;
    }
    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        int value = rand() % testSize + 1;
        data2.equal_range(value);
        data2.lower_bound(value);
        data2.upper_bound(value);
    }
    data2.erase(data2.begin(), data2.end());
    data1.clear();
    map<float, std::string> data4;
    for (size_t i = 0; i < testSize; ++i) {
        srand(i);
        float value = rand() % testSize + 1;
        data4.insert(make_pair(value, "melaena"));
        data4.insert(make_pair(value + testSize, "S y"));
    }
    data4.clear();
}

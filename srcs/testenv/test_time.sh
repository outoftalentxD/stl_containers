#!/bin/bash
echo "FT VECTOR"
g++ -Wall -Wextra -Werror -std=c++98 ft_vector.cpp -o app
time ./app
echo

echo "STD VECTOR"
g++ -Wall -Wextra -Werror -std=c++98 std_vector.cpp -o app
time ./app
echo

echo "FT MAP"
g++ -Wall -Wextra -Werror -std=c++98 ft_map.cpp -o app
time ./app
echo

echo "STD MAP"
g++ -Wall -Wextra -Werror -std=c++98 std_map.cpp -o app
time ./app
echo

./app
rm -rf app

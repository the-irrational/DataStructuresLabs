set -u
g++ -std=c++11 -ggdb myBinaryMinHeap.hpp
g++ -std=c++11 -ggdb  test_main.cpp
for i in 1 2 3 4 5 6 7 8 9 10
do
  ./a.out "inputs/instance$i.txt" "output$i.txt"
  if cmp "outputs/output$i.txt" "output$i.txt"; then
    echo $i=good
  else
    echo $i=bad
  fi
done

g++ -std=c++11 -ggdb myDlList.hpp
g++ -std=c++11 -ggdb  test_main.cpp
for i in 1 2 3 4 5 6 7 8 9 10
do
  ./a.out "Instance_Files/instance$i.txt" "output$i.txt"
  if cmp "Output_Files/output$i.txt" "output$i.txt"; then
    echo good
  else
    echo diff
  fi
done

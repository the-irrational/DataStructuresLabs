g++ -g -std=c++11 mySorting.hpp
g++ -g -std=c++11 main.cpp
for i in 1 2
do
./a.out instances/instance$i.txt > myoutputs/output$i.txt
if diff -b outputs/output$i.txt myoutputs/output$i.txt > myoutputs/logs/diff$i.txt
then echo "$i = good"
else echo "$i = bad"
fi
done

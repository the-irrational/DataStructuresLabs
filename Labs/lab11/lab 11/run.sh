g++ -g -std=c++11 myGraph_r670r375.hpp
g++ -g -std=c++11 main.cpp
for i in 2 #2 3 4 5 6 7 8 9 10
do
START_TIME=$SECONDS
echo "instance $i"
./a.out instances/instance$i.txt > myoutputs/output$i.txt
ELAPSED_TIME=$(($SECONDS - $START_TIME))
echo "Elapsed time: $ELAPSED_TIME"
if diff -b outputs/output$i.txt myoutputs/output$i.txt > logs/diff$i.txt
then echo "$i = good"
else echo "$i = bad"
fi
done

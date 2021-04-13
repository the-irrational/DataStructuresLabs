g++ -g -std=c++11 myGraph.hpp
g++ -g -std=c++11 main.cpp
for i in 1 2 3 4 5 6 7 8 9 10
do
start=$(date +%s)
/usr/bin/time -f "process $i maxx RSS %M kbytes" ./a.out instances/instance$i.txt > myoutputs/output$i.txt
end=$(date +%s)
echo "$i = $(expr $end - $start) seconds"
done


set -u
g++ -std=c++11 -ggdb myStack.hpp
g++ -std=c++11 -ggdb myQueue.hpp
g++ -std=c++11 -ggdb  test_main.cpp
for i in 1 2 3 4 5 6 7 8 9 10
do
  ./a.out "Instance(Input))Files/instance$i.txt" "stackoutput$i.txt" "queueoutput$i.txt"
  if cmp "Output_files_stack/output$i"_"stack.txt" "stackoutput$i.txt"; then
    echo stack=good
  else
    echo stack=bad
  fi
  if cmp "Output_files_queue/output$i"_"queue.txt" "queueoutput$i.txt"; then
    echo queue=good
  else
    echo queue=bad
  fi
done

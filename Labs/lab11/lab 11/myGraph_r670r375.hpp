#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;
class vertex
{
public:
  vector<pair<int, int>>* adj;
  int dist;
  bool known;
  pair<int, int>* path;
  vertex()
  {
    adj = new vector<pair<int, int>>();
    path = new pair<int, int>();
  }
  ~vertex()
  {
    delete adj;
    delete path;
  }
};
using namespace std;
class myGraph
{
public:
  myGraph( char* filename )
  {
    size = initSize(filename) + 1;
    graph = new vertex[size];
    for (int i = 0; i < size; i++)
    {
      graph[i].adj = new vector<pair<int, int>>();
    }
    ifstream fin;
    fin.open(filename);
    if (fin.is_open())
    {
      string line;
      while (getline(fin, line, ','))
      {
        int index = stoi(line);
        getline(fin, line, ',');
        int t = stoi(line);
        getline(fin, line, ',');
        graph[index].adj->push_back(make_pair(t, stoi(line)));
      }
    }
  }
  ~myGraph()
  {
    //delete anything
    delete[] graph;
  }
  void print2()
  {
    for (int i = 0; i < size; i++)
    {
      cout<<i<<":";
      for (int j = 0; j < graph[i].adj->size(); j++)
      {
        cout<<" "<<graph[i].adj->at(j).second;
      }
      cout<<endl;
    }
  }
  void dijkstra(int source)
  {
    for (int i = 0; i < size; i++)
    {
      delete graph[i].path;
      graph[i].dist = INT_MAX;
      graph[i].known = false;
      graph[i].path = new pair<int, int>(-1, INT_MAX);
    }
    ts = source;
    graph[source].dist = 0;
    int count = 0;
    while (count < size)
    {
      source = getTotMin();
      graph[source].known = true;
      for (int i = 0; i < graph[source].adj->size(); i++)
      {
        int cvw = graph[source].adj->at(i).second;
        if (!graph[graph[source].adj->at(i).first].known)
        {
          if (graph[source].dist + cvw < graph[graph[source].adj->at(i).first].dist)
          {
              graph[graph[source].adj->at(i).first].dist = cvw + graph[source].dist;
              graph[graph[source].adj->at(i).first].path->first = source;
              graph[graph[source].adj->at(i).first].path->second = graph[source].adj->at(i).second;
          }
        }
      }
      count++;
    }
  }
  void printPath(int i)
  {
    //give recursive def
    if (graph[i].dist != 0)
    {
      printPath(graph[i].path->first);
      cout << " ";
    }
    cout << i;
  }
  int computePathCost(int i)
  {
    //give recursive def
    return graph[i].dist;
  }
  int initSize(char* filename)
  {
    ifstream fin;
    fin.open(filename);
    if(fin.is_open())
    {
      //get the size first. minimize resizing
      fin.seekg(-1, ios_base::end);
      char ch;
      int loop = 0;
      while(loop<4)
      {
        fin.get(ch);

        if((int)fin.tellg() <= 1)
        {
          fin.seekg(0);
          loop = false;
        }
        else if (ch == ',')
        {
          loop++;
          if (loop < 4)
            fin.seekg(-2, ios_base::cur);
        }
        else
        {
          fin.seekg(-2, ios_base::cur);
        }
      }
      string line;
      getline(fin, line, ',');
      return stoi(line);
    }
    else
    {
      cout<<"Cannot open file!\n";
      return 0;
    }
  }
private:
  vertex* graph;
  int size;
  int ts;
  /*vertex getMin(vertex source)
  {
    pair<int, int> min = source.adj->at(0);
    for (int j = 0; j < source.adj->size(); j++)
    {
      if (min.second > source.adj->at(j).second && !graph[source.adj->at(j).first].known || graph[min.first].known && !graph[source.adj->at(j).first].known)
      {
        min = source.adj->at(j);
      }
    }
    return graph[min.first];
  }
  int getMin(vertex source)
  {
    //return index of mininum
    int tempval = 0;
    int retval = source.adj->at(tempval).first;
    for (int j = 0; j < source.adj->size(); j++)
    {
      if (source.adj->at(tempval).second > source.adj->at(j).second || graph[retval].known && !graph[source.adj->at(j).first].known)
      {
        tempval = j;
        retval = source.adj->at(j).first;
      }
    }
    return retval;
  }*/
  int getTotMin()
  {
    //return index of mininum
    int retval = INT_MAX, index;
    for (int j = 0; j < size; j++)
    {
      if (!graph[j].known && retval > graph[j].dist)
      {
        retval = graph[j].dist;
        index = j;
      }
    }
    //cout<<"Total min set: "<<index<<endl;
    return index;
  }
  void testWrite()
  {
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < graph[i].adj->size(); j++)
      {
        cout<<i<<","<<graph[i].adj->at(j).first<<","<<graph[i].adj->at(j).second<<",";
      }
    }
  }
};

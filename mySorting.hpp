#include <vector>
#include <iostream>
using namespace std;
template <typename Comparable>
void quickSort(vector<Comparable>& a, bool reverse) {
  quickSort(a, 0, static_cast<int>(a.size()-1), reverse);
}
template <typename Comparable>
void quickSort(vector<Comparable>& a) {
  bool t = false;
  quickSort(a, 0, static_cast<int>(a.size()-1), false);
}
template <typename Comparable>
void quickSort(vector<Comparable>& a, int left, int right, bool reverse) {
  if (!reverse) {
    if (left + 10 <= right) {
      const Comparable & pivot = median3(a, left, right, reverse);
      cout<<pivot<<endl;
      int i = left, j = right - 1;
      for (; ;) {
        while (a[++i] < pivot) { }
        while (pivot < a[--j]) { }
        if (i < j)
          swap(a[i], a[j]);
        else
          break;
      }
      swap(a[i], a[right - 1]);
      quickSort(a, left, i - 1);
      quickSort(a, i + 1, right);
    }
    else
      insertionSort(a, left, right, reverse);
  }
  else {
    //reverse this code
    if (left + 10 <= right) {
      const Comparable & pivot = median3(a, left, right, reverse);
      cout<<pivot;
      int i = left, j = right - 1;
      for (; ;) {
        while (a[++i] > pivot) { }
        while (pivot > a[--j]) { }
        if (i > j)
          swap(a[i], a[j]);
        else
          break;
      }
      swap(a[i], a[right - 1]);
      quickSort(a, left, i - 1);
      quickSort(a, i + 1, right);
    }
    else
      insertionSort(a, left, right, reverse);
  }
}
template <typename Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right, bool reverse) {
  //figure 7.16
  int center = (left + right) / 2;
  if (!reverse) {
    if (a[center] < a[left])
      swap(a[left], a[center]);
    if (a[right] < a[left])
      swap(a[left], a[right]);
    if(a[right] < a[center])
      swap(a[center], a[right]);
    swap(a[center], a[right-1]);
    return a[right-1];
  }
  else {
    if (a[center] > a[left])
      swap(a[left], a[center]);
    if (a[right] > a[left])
      swap(a[left], a[right]);
    if(a[right] > a[center])
      swap(a[center], a[right]);
    swap(a[center], a[right-1]);
    return a[right-1];
  }
}
template <typename Comparable>
void insertionSort(vector<Comparable> & a, int left, int right, bool reverse) {
  //figure 7.2
  if (!reverse) {
    for (int p = 1; p < a.size(); ++p) {
      Comparable tmp = move(a[p]);
      int j;
      for (j = p; j > 0 && tmp < a[j-1]; --j)
        a[j] = move(a[j - 1]);
      a[j] = move(tmp);
    }
  }
  else {
    //REVERSE IT BITCH
  }
}

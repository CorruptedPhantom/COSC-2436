// Linear Search in C++

#include <iostream>
using namespace std;

int search(int array[], int n, int x) {

  // Going through array sequencially
  for (int i = 0; i < n; i++)
    if (array[i] == x)
      return i;
  return -1;
}

int binarySearch(int array[], int x, int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (array[mid] == x)
      return mid;

    if (array[mid] < x)
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}

int main() {
  cout<<"Insert: 2, 4, 0, 1, 9"<<endl;
  int array[] = {2, 4, 0, 1, 9};
  int x = 1;
  int n = sizeof(array) / sizeof(array[0]);

  cout<<"Linear Search:"<<endl;
  int result = search(array, n, x);

  (result == -1) ? cout << "Element not found" : cout << "Element found at index: " << result<<endl;

  cout<<"Binary Search:"<<endl;
  int result2 = binarySearch(array, x, 0, n - 1);
  if (result == -1)
    printf("Not found");
  else
    printf("Element is found at index %d", result);

}

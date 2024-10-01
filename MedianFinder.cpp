//Question:
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

// For example, for arr = [2,3,4], the median is 3.
// For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
// Implement the MedianFinder class:

// MedianFinder() initializes the MedianFinder object.
// void addNum(int num) adds the integer num from the data stream to the data structure.
// double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.


//Code:
//Adding a number: O(log n)
//Finding a median: O(1)

//Space complexity: O(N)
#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    // Max-heap to store the smaller half of the numbers
    priority_queue<int> smallHalf; 
    // Min-heap to store the larger half of the numbers
    priority_queue<int, vector<int>, greater<int>> largeHalf;

    // Constructor
    MedianFinder() {
        
    }
    
    // Function to add a number
    void addNum(int num) {
        // If smallHalf is empty, just add the number there
        if (smallHalf.empty()) {
            smallHalf.push(num);
        }
        // If both heaps are of the same size, decide where to put the new number
        else if (smallHalf.size() == largeHalf.size()) {
            if (largeHalf.top() < num) {
                smallHalf.push(largeHalf.top());
                largeHalf.pop();
                largeHalf.push(num);
            } else {
                smallHalf.push(num);
            }
        }
        // If smallHalf has more elements than largeHalf
        else {
            if (smallHalf.top() < num) {
                largeHalf.push(num);
            } else {
                largeHalf.push(smallHalf.top());
                smallHalf.pop();
                smallHalf.push(num);
            }
        }
    }
    
    // Function to find the median
    double findMedian() {
        // If both heaps are of equal size, return the average of the tops
        if (smallHalf.size() == largeHalf.size()) {
            return ((double)smallHalf.top() + (double)largeHalf.top()) / 2.0;
        }
        // If smallHalf has more elements, return the top of smallHalf
        return (double)smallHalf.top();
    }
};

int main(){
    MedianFinder MF;
    MF.addNum(1);
    MF.addNum(2);
    cout<<MF.findMedian()<<endl;
    MF.addNum(3);
    cout<<MF.findMedian()<<endl;
    return 0;
}

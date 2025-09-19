// testcase for size() and memberOf()

#include <iostream>
#include "recursive.h"
#include  "p2.h"
using namespace std;


void checkMemberOf(list_t list, int val, bool expected) {
    bool result = memberOf(list, val);
    std::cout << "memberOf(list, " << val << ") = " << (result ? "Yes" : "No")
              << " | Expected: " << (expected ? "Yes" : "No")
              << " | Test " << (result == expected ? "PASSED" : "FAILED") << std::endl;
}

void checkSize(list_t list, int expected) {
    int result = size(list);
    std::cout << "size(list) = " << result 
              << " | Expected: " << expected
              << " | Test " << (result == expected ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    // Create some test lists
    list_t emptyList = list_make(); // Empty list
    list_t singleItemList = list_make(42, emptyList); // List with one element: [42]
    list_t multiItemList = list_make(10, list_make(20, list_make(30, emptyList))); // List: [10, 20, 30]
    list_t listWithDuplicates = list_make(5, list_make(10, list_make(5, emptyList))); // List: [5, 10, 5]
    list_t largeList = list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, emptyList))))); // List: [1, 2, 3, 4, 5]

    // Test memberOf function with various cases
    std::cout << "Testing memberOf:" << std::endl;

    // Case 1: Check if an element is in the empty list
    checkMemberOf(emptyList, 42, false);

    // Case 2: Check if an element is in a single-item list
    checkMemberOf(singleItemList, 42, true);
    checkMemberOf(singleItemList, 10, false);

    // Case 3: Check if an element is in a multi-item list
    checkMemberOf(multiItemList, 10, true);
    checkMemberOf(multiItemList, 20, true);
    checkMemberOf(multiItemList, 30, true);
    checkMemberOf(multiItemList, 100, false);

    // Case 4: Check if an element appears multiple times in a list
    checkMemberOf(listWithDuplicates, 5, true);  // 5 appears twice
    checkMemberOf(listWithDuplicates, 10, true);
    checkMemberOf(listWithDuplicates, 15, false);

    // Case 5: Check if an element is in a large list
    checkMemberOf(largeList, 3, true);
    checkMemberOf(largeList, 6, false);

    // Test size function with various cases
    std::cout << "\nTesting size:" << std::endl;

    // Case 1: Size of the empty list
    checkSize(emptyList, 0);

    // Case 2: Size of a single-item list
    checkSize(singleItemList, 1);

    // Case 3: Size of a multi-item list
    checkSize(multiItemList, 3);

    // Case 4: Size of a list with duplicates
    checkSize(listWithDuplicates, 3);

    // Case 5: Size of a large list
    checkSize(largeList, 5);

    return 0;
}
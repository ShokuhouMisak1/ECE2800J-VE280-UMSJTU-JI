#include <iostream>
#include "recursive.h"
#include  "p2.h"
using namespace std;



// Helper function to check the dot product and expected result
void checkDot(list_t v1, list_t v2, int expected) {
    int result = dot(v1, v2);
    std::cout << "dot(v1, v2) = " << result 
              << " | Expected: " << expected
              << " | Test " << (result == expected ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to check if the list is increasing
void checkIsIncreasing(list_t v, bool expected) {
    bool result = isIncreasing(v);
    std::cout << "isIncreasing(v) = " << (result ? "Yes" : "No")
              << " | Expected: " << (expected ? "Yes" : "No")
              << " | Test " << (result == expected ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    // Create some test lists for the dot product and isIncreasing tests
    list_t emptyList = list_make(); // Empty list
    list_t singleItemList = list_make(42, emptyList); // List with one element: [42]
    list_t twoElementList1 = list_make(1, list_make(2, emptyList)); // List: [1, 2]
    list_t twoElementList2 = list_make(3, list_make(4, emptyList)); // List: [3, 4]
    list_t threeElementList1 = list_make(1, list_make(2, list_make(3, emptyList))); // List: [1, 2, 3]
    list_t threeElementList2 = list_make(4, list_make(5, list_make(6, emptyList))); // List: [4, 5, 6]
    list_t longerList = list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, emptyList))))); // List: [1, 2, 3, 4, 5]

    // Test dot function with various cases
    std::cout << "Testing dot product:" << std::endl;

    // Case 1: Single item lists
    checkDot(singleItemList, singleItemList, 42 * 42); // Expected: 1764

    // Case 2: Two-element lists
    checkDot(twoElementList1, twoElementList2, 1 * 3 + 2 * 4); // Expected: 11

    // Case 3: Three-element lists
    checkDot(threeElementList1, threeElementList2, 1 * 4 + 2 * 5 + 3 * 6); // Expected: 32

    // Case 4: Lists with different lengths
    checkDot(longerList, threeElementList1, 1 * 1 + 2 * 2 + 3 * 3); // Expected: 14 (ignores extra elements of longerList)

    // Test isIncreasing function with various cases
    std::cout << "\nTesting isIncreasing:" << std::endl;

    // Case 1: Empty list (increasing by definition)
    checkIsIncreasing(emptyList, true);

    // Case 2: Single element list (increasing by definition)
    checkIsIncreasing(singleItemList, true);

    // Case 3: Two-element increasing list
    checkIsIncreasing(twoElementList1, true); // [1, 2] is increasing

    // Case 4: Two-element non-increasing list
    list_t nonIncreasingList = list_make(2, list_make(1, emptyList)); // List: [2, 1]
    checkIsIncreasing(nonIncreasingList, false);

    // Case 5: Multi-element increasing list with duplicates
    list_t increasingWithDuplicates = list_make(1, list_make(2, list_make(2, list_make(3, emptyList)))); // List: [1, 2, 2, 3]
    checkIsIncreasing(increasingWithDuplicates, true);

    // Case 6: Multi-element non-increasing list
    list_t nonIncreasingLongList = list_make(1, list_make(2, list_make(3, list_make(2, list_make(5, emptyList))))); // List: [1, 2, 3, 2, 5]
    checkIsIncreasing(nonIncreasingLongList, false);
    
    // Case 7: List with a same value
    list_t uniformList = list_make(114514, list_make( 114514, list_make(114514, list_make())));
    checkIsIncreasing(uniformList, true);

    return 0;
}
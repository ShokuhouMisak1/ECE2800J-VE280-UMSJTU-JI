#include <iostream>
#include "recursive.h"
#include  "p2.h"
using namespace std;

// Helper function to print a list (assuming list_print exists)
void printList(list_t list) {
    list_print(list);
    std::cout << std::endl;
}

// Helper function to check if two lists are equal
bool list_equal(list_t l1, list_t l2) {
    if (list_isEmpty(l1) && list_isEmpty(l2)) {
        return true;
    } else if (list_isEmpty(l1) || list_isEmpty(l2)) {
        return false;
    } else if (list_first(l1) != list_first(l2)) {
        return false;
    } else {
        return list_equal(list_rest(l1), list_rest(l2));
    }
}

// Helper function to check filter_odd
void checkFilterOdd(list_t list, list_t expected) {
    list_t result = filter_odd(list);
    std::cout << "filter_odd(list) = ";
    printList(result);
    std::cout << "Expected: ";
    printList(expected);
    std::cout << "Test " << (list_equal(result, expected) ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to check unique
void checkUnique(list_t list, list_t expected) {
    list_t result = unique(list);
    std::cout << "unique(list) = ";
    printList(result);
    std::cout << "Expected: ";
    printList(expected);
    std::cout << "Test " << (list_equal(result, expected) ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    // Create an empty list
    list_t emptyList = list_make(); // Empty list

    // Test cases for filter_odd
    std::cout << "Testing filter_odd function:" << std::endl;

    // List: (-3, 2, -1, 4, 5, -6, -7)
    list_t listWithNegatives = list_make(-3, list_make(2, list_make(-1, list_make(4, 
                        list_make(5, list_make(-6, list_make(-7, emptyList)))))));
    // Expected: (-3, -1, 5, -7)
    list_t expectedNegOdd = list_make(-3, list_make(-1, list_make(5, list_make(-7, emptyList))));

    // List: (1, -2, 3, -4, 5, -6, 7)
    list_t mixedPositiveNegative = list_make(1, list_make(-2, list_make(3, list_make(-4, 
                            list_make(5, list_make(-6, list_make(7, emptyList)))))));
    // Expected: (1, 3, 5, 7)
    list_t expectedMixedOdd = list_make(1, list_make(3, list_make(5, list_make(7, emptyList))));

    // Run filter_odd tests
    checkFilterOdd(listWithNegatives, expectedNegOdd);  // List with negative odd numbers
    checkFilterOdd(mixedPositiveNegative, expectedMixedOdd);  // Mixed positive and negative

    // Test cases for unique
    std::cout << "Testing unique function:" << std::endl;

    // List: (-1, -1, 0, 2, -3, -3, 5, 0)
    list_t listWithDuplicatesNeg = list_make(-1, list_make(-1, list_make(0, list_make(2, 
                        list_make(-3, list_make(-3, list_make(5, list_make(0, emptyList))))))));
    // Expected: (-1, 0, 2, -3, 5)
    list_t expectedUniqueNeg = list_make(-1, list_make(0, list_make(2, list_make(-3, list_make(5, emptyList)))));

    // List: (10, -10, 20, -20, 30, -30, 10, -10, 30)
    list_t largeUniqueNegList = list_make(10, list_make(-10, list_make(20, list_make(-20, 
                        list_make(30, list_make(-30, list_make(10, list_make(-10, list_make(30, emptyList)))))))));
    // Expected: (10, -10, 20, -20, 30, -30)
    list_t expectedLargeUnique = list_make(10, list_make(-10, list_make(20, list_make(-20, list_make(30, list_make(-30, emptyList))))));

    // Run unique tests
    checkUnique(listWithDuplicatesNeg, expectedUniqueNeg);  // Duplicates with negative numbers
    checkUnique(largeUniqueNegList, expectedLargeUnique);  // Larger list with positives and negatives

    return 0;
}
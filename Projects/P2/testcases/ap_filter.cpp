#include "recursive.h"
#include <iostream>
#include "p2.h"

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
    } else if (list_first(l1) != list_first(l1)) {
        return false;
    } else {
        return list_equal(list_rest(l1), list_rest(l2));
    }
}

// Helper function to check isArithmeticSequence
void checkIsArithmeticSequence(list_t list, bool expected) {
    bool result = isArithmeticSequence(list);
    std::cout << "isArithmeticSequence(list) = " << result << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Test " << (result == expected ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to check filter
void checkFilter(list_t list, list_t expected, bool (*fn)(int)) {
    list_t result = filter(list, fn);
    std::cout << "filter(list) = ";
    printList(result);
    std::cout << "Expected: ";
    printList(expected);
    std::cout << "Test " << (list_equal(result, expected) ? "PASSED" : "FAILED") << std::endl;
}

// Predicate function for testing filter (returns true if the number is even)
bool isEven(int a) {
    return a % 2 == 0;
}

int main() {
    // Create an empty list
    list_t emptyList = list_make(); // Empty list

    // Test cases for isArithmeticSequence
    std::cout << "Testing isArithmeticSequence function:" << std::endl;

    // Longer list with positive and negative numbers (arithmetic sequence, step -5)
    // List: (15, 10, 5, 0, -5, -10)
    list_t longArithmeticSeq = list_make(15, list_make(10, list_make(5, list_make(0, 
                         list_make(-5, list_make(-10, emptyList))))));
    checkIsArithmeticSequence(longArithmeticSeq, true);  // Expected: true

    // Longer list with negative numbers (arithmetic sequence, step -3)
    // List: (-3, -6, -9, -12, -15, -18, -21)
    list_t negArithmeticSeq = list_make(-3, list_make(-6, list_make(-9, list_make(-12, 
                         list_make(-15, list_make(-18, list_make(-21, emptyList)))))));
    checkIsArithmeticSequence(negArithmeticSeq, true);  // Expected: true

    // Longer list (not an arithmetic sequence)
    // List: (5, 8, 15, 10, -5, -10)
    list_t nonArithmeticSeqLong = list_make(5, list_make(8, list_make(15, list_make(10, 
                         list_make(-5, list_make(-10, emptyList))))));
    checkIsArithmeticSequence(nonArithmeticSeqLong, false);  // Expected: false

    // Test cases for filter
    std::cout << "Testing filter function with isEven predicate:" << std::endl;

    // Longer list with mixed positive and negative numbers
    // List: (1, 2, 3, 4, -5, -6, 7, 8, -9, 10)
    list_t mixedLongList = list_make(1, list_make(2, list_make(3, list_make(4, 
                          list_make(-5, list_make(-6, list_make(7, list_make(8, 
                          list_make(-9, list_make(10, emptyList))))))))));
    // Expected: (2, 4, -6, 8, 10)
    list_t expectedEvenList = list_make(2, list_make(4, list_make(-6, list_make(8, 
                         list_make(10, emptyList)))));
    checkFilter(mixedLongList, expectedEvenList, isEven);  // Expected: (2, 4, -6, 8, 10)

    // Longer list with only negative numbers
    // List: (-10, -9, -8, -7, -6, -5, -4, -3, -2, -1)
    list_t negativeList = list_make(-10, list_make(-9, list_make(-8, list_make(-7, 
                         list_make(-6, list_make(-5, list_make(-4, list_make(-3, 
                         list_make(-2, list_make(-1, emptyList))))))))));
    // Expected: (-10, -8, -6, -4, -2)
    list_t expectedNegEvenList = list_make(-10, list_make(-8, list_make(-6, list_make(-4, 
                         list_make(-2, emptyList)))));
    checkFilter(negativeList, expectedNegEvenList, isEven);  // Expected: (-10, -8, -6, -4, -2)

    return 0;
}

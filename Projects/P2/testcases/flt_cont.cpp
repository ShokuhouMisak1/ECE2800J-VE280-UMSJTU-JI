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
    } else if (list_first(l1) != list_first(l2)) {
        return false;
    } else {
        return list_equal(list_rest(l1), list_rest(l2));
    }
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

// Predicate function for testing filter (returns true if the number is divisible by 7)
bool isDivisibleBy7(int a) {
    return a % 7 == 0;
}

int main() {
    // Create an empty list
    list_t emptyList = list_make(); // Empty list

    // Test cases for filter with isDivisibleBy7 predicate
    std::cout << "Testing filter function with isDivisibleBy7 predicate:" << std::endl;

    // Longer list with mixed positive and negative numbers
    // List: (14, 21, 28, -7, 35, 5, 10, -14, 49)
    list_t mixedLongList = list_make(14, list_make(21, list_make(28, list_make(-7,
                          list_make(35, list_make(5, list_make(10, list_make(-14,
                          list_make(49, emptyList)))))))));
    // Expected: (14, 21, 28, -7, 35, -14, 49)
    list_t expectedDivBy7List = list_make(14, list_make(21, list_make(28, list_make(-7,
                          list_make(35, list_make(-14, list_make(49, emptyList)))))));
    checkFilter(mixedLongList, expectedDivBy7List, isDivisibleBy7);  // Expected: (14, 21, 28, -7, 35, -14, 49)

    // Longer list with no numbers divisible by 7
    // List: (1, 2, 3, 4, 5, 6, 8, 9, 10)
    list_t noDivBy7List = list_make(1, list_make(2, list_make(3, list_make(4,
                          list_make(5, list_make(6, list_make(8, list_make(9,
                          list_make(10, emptyList)))))))));
    // Expected: ()
    checkFilter(noDivBy7List, emptyList, isDivisibleBy7);  // Expected: ()

    // List with only numbers divisible by 7
    // List: (7, 14, 21, 28, 35, 42, 49, 56)
    list_t allDivBy7List = list_make(7, list_make(14, list_make(21, list_make(28,
                          list_make(35, list_make(42, list_make(49, list_make(56,
                          emptyList))))))));
    // Expected: (7, 14, 21, 28, 35, 42, 49, 56)
    checkFilter(allDivBy7List, allDivBy7List, isDivisibleBy7);  // Expected: (7, 14, 21, 28, 35, 42, 49, 56)

    // Mixed list with negative and positive numbers (with no numbers divisible by 7)
    // List: (-1, -2, -3, 5, 10, 11, -8, 9, -4)
    list_t mixedNoDivBy7 = list_make(-1, list_make(-2, list_make(-3, list_make(5,
                          list_make(10, list_make(11, list_make(-8, list_make(9,
                          list_make(-4, emptyList)))))))));
    // Expected: ()
    checkFilter(mixedNoDivBy7, emptyList, isDivisibleBy7);  // Expected: ()

    return 0;
}

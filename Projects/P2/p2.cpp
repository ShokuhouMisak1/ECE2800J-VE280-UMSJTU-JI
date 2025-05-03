#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

//List Functions


int size(list_t list){
    if(list_isEmpty(list)) {
        return 0;
    }
    else{
        return 1+size(list_rest(list));
    }
}
// EFFECTS: Returns the number of elements in "list".
// Returns zero if "list" is empty.


bool memberOf(list_t list, int val){
    if(list_isEmpty(list)) {
        return false;
    }
    else{
        if(list_first(list) == val){
            return true;
        }
        else{
            return memberOf(list_rest(list), val);
        }
    }
}
// EFFECTS: Returns true if the value "val" appears in "list".
// Returns false otherwise.


int dot(list_t v1, list_t v2){
    if(list_isEmpty(v1) || list_isEmpty(v2)){
        return 0;
    }
    else{
        return list_first(v1)*list_first(v2) + dot(list_rest(v1),list_rest(v2));
    }
}
// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
// product of the two vectors. If one list is longer
// than the other, ignore the longer part of the vector.

bool isIncreasing(list_t v){
    if(list_isEmpty(v) || list_isEmpty(list_rest(v))){
        return true;
    }
    else{
        if(list_first(v) <= list_first(list_rest(v))){
            return isIncreasing(list_rest(v));
        }
        else{
            return false;
        }
    }
}
// EFFECTS: Checks if the list of integers is increasing.
// A list is increasing if and only if no element
// is smaller than its previous element. By default,
// an empty list and a list of a single element are
// increasing.

static list_t reverse_helper(list_t list, list_t reverse_list) {
    if (list_isEmpty(list)) {
        return reverse_list;
    }
    else {
        return reverse_helper(list_rest(list), list_make(list_first(list),reverse_list));
    }
}
//helper for reverse

list_t reverse(list_t list) {
    list_t reverse_list = list_make();
    return reverse_helper(list, reverse_list);
}
//EFFECTS: Returns the reverse of "list".

static list_t append_helper(list_t first, list_t second){
    if(list_isEmpty(list_rest(first))){
        return list_make(list_first(first),second);
    }
    else{
        return list_make(list_first(first),append(list_rest(first),second));
    }
}
// helper for append

list_t append(list_t first, list_t second){
    if(list_isEmpty(first)){
        return second;
    }
    else {
        return append_helper(first,second);
    }
}
// EFFECTS: Returns the list (first second).

static bool isArithmeticSequence_helper(list_t v, int difference){
    if(list_isEmpty(v) || list_isEmpty(list_rest(v))){
        return true;
    }
    else{
        if(list_first(list_rest(v)) - list_first(v) == difference){
            return isArithmeticSequence_helper(list_rest(v), difference);
        }
        else{
            return false;
        }
    }
}
//helper for isArithmeticSequence

bool isArithmeticSequence(list_t v){
    if(list_isEmpty(v) || list_isEmpty(list_rest(v))){
        return true;
    }
    else{
        int difference = list_first(list_rest(v)) - list_first(v);
        return isArithmeticSequence_helper(v,difference);
    }
}
// EFFECTS: Checks if the list of integers forms an
// arithmetic sequence. By default, an empty list and
// a list of a single element are arithmetic sequences.


static int list_last(list_t list){
    if(list_isEmpty(list_rest(list))){
        return list_first(list);
    }
    else{
        return list_last(list_rest(list));
    }
}
// REQUIRES: non-empty list
// EFFECTS: return the last value of the list

static list_t list_prior(list_t list){
    if(list_isEmpty(list_rest(list))){
        return list_make();
    }
    else{
        list_t rest_prior = list_prior(list_rest(list));
        return list_make(list_first(list), rest_prior);
    }
}
// REQUIRES: non-empty list
// EFFECTS: return the list containg all of the member except the last member

static list_t filter_odd_helper(list_t list,list_t odd_list){
    if(list_isEmpty(list)){
        return odd_list;
    }
    else{
        if((list_last(list)%2)==1 || (list_last(list)%2)==-1){
            return filter_odd_helper(list_prior(list),list_make(list_last(list),odd_list));
        }
        else{
            return filter_odd_helper(list_prior(list),odd_list);
        }
    }
}
//helper for filter_odd

list_t filter_odd(list_t list){
    if(list_isEmpty(list)){
        return list;
    }
    else{
        list_t odd_list = list_make();
        return filter_odd_helper(list,odd_list);
    }
}
// EFFECTS: Returns a new list containing only the elements of the
// original "list" which are odd in value,
// in the order in which they appeared in list.

static list_t filter_helper(list_t list,list_t fn_list,bool (*fn)(int)){
    if(list_isEmpty(list)){
        return fn_list;
    }
    else{
        if(fn(list_last(list))){
            return filter_helper(list_prior(list),list_make(list_last(list),fn_list),fn);
        }
        else{
            return filter_helper(list_prior(list),fn_list,fn);
        }
    }
}
//helper for filter

list_t filter(list_t list, bool (*fn)(int)){
    if(list_isEmpty(list)){
        return list;
    }
    else{
        list_t fn_list = list_make();
        return filter_helper(list,fn_list,fn);
    }
}
// EFFECTS: Returns a list containing precisely the elements of "list"
// for which the predicate fn() evaluates to true, in the
// order in which they appeared in list

static list_t list_push(int num, list_t list){
    list = reverse(list);
    list = list_make(num,list);
    return reverse(list);
}
// add a number to the last of the list

bool if_unique(int num, list_t unique_list){
    if(list_isEmpty(unique_list)){
        return true;
    }
    else{
        if(num==list_first(unique_list)){
            return false;
        }
        else{
            return if_unique(num,list_rest(unique_list));
        }
    }
}
// judge whther a number is unique

static list_t unique_helper(list_t list,list_t unique_list){
    if(list_isEmpty(list)){
        return unique_list;
    }
    if(if_unique(list_first(list),unique_list)){
        unique_list = list_push(list_first(list),unique_list);
    }
    return unique_helper(list_rest(list),unique_list);
}
// helper for unique

list_t unique(list_t list){
    if(list_isEmpty(list)){
        return list;
    }
    else{
        list_t unique_list = list_make();
        return unique_helper(list,unique_list);
    }
}
// EFFECTS: Returns a new list comprising of each unique element
// in "list". The order is determined by the first
// occurrence of each unique element in "list".


list_t insert_list(list_t first, list_t second, unsigned int n){
    if(n==0){
        return append(second,first);
    }
    else{
        return list_make(list_first(first),insert_list(list_rest(first),second,n-1));
    }
}
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
// "first", followed by all elements of "second",
// followed by any remaining elements of "first".

static list_t chop_helper(list_t list, unsigned int n){
    if(n==0){
        return list_make();
    }
    else{
        return list_make(list_first(list),chop_helper(list_rest(list),n-1));
    }
}

list_t chop(list_t list, unsigned int n){
    if(n==0){
        return list;
    }
    else{
        unsigned int num = size(list) -n;
        return chop_helper(list,num);
    }
}
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
// elements.


//Tree Functions
int tree_sum(tree_t tree){
    if(tree_isEmpty(tree)){
        return 0;
    }
    else{
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}
// EFFECTS: Returns the sum of all elements in "tree". 
// Returns zero if "tree" is empty.

bool tree_search(tree_t tree, int val){
    if(tree_isEmpty(tree)){
        return false;
    }
    else{
        if(tree_elt(tree) == val){
            return true;
        }
        else{
            return tree_search(tree_left(tree),val) || tree_search(tree_right(tree),val);
        }
    }
}
// EFFECTS: Returns true if the value "val" appears in "tree".
// Returns false otherwise.

static int max(int a,int b){
    if(a>=b){
        return a;
    }
    return b;
}
// Return the larger value of a and b


int depth(tree_t tree){
    if(tree_isEmpty(tree)){
        return 0;
    }
    else{
        return max(1+depth(tree_left(tree)),1+depth(tree_right(tree)));
    }
}
// EFFECTS: Returns the depth of "tree", which equals the number of
// layers of nodes in the tree.
// Returns zero if "tree" is empty.


int tree_max(tree_t tree){
    if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return tree_elt(tree);
    else{
        if(tree_isEmpty(tree_left(tree))){
            return max(tree_elt(tree),tree_max(tree_right(tree)));
        }
        else if(tree_isEmpty(tree_right(tree))){
            return max(tree_elt(tree),tree_max(tree_left(tree)));
        }
        else{
            return max(tree_elt(tree),max(tree_max(tree_left(tree)),tree_max(tree_right(tree))));
        }
    }
}
// REQUIRES: "tree" is non-empty.
//
// EFFECTS: Returns the largest element in "tree".


list_t traversal(tree_t tree){
    list_t list = list_make();
    if(tree_isEmpty(tree)){
        return list;
    }
    else{
        return append(traversal(tree_left(tree)),list_make(tree_elt(tree),traversal(tree_right(tree))));
    }
}
// EFFECTS: Returns the elements of "tree" in a list using an
// in-order traversal. An in-order traversal prints
// the "left most" element first, then the second-left-most,
// and so on, until the right-most element is printed.
//
// For any node, all the elements of its left subtree
// are considered as on the left of that node and
// all the elements of its right subtree are considered as
// on the right of that node.

static bool smaller(int a, int b){
    if(a<b){
        return true;
    }
    return false;
}
// get the smaller value

static bool larger(int a, int b){
    if(a>b){
        return true;
    }
    return false;
}
//get the larger value

bool tree_hasMonotonicPath_helper(tree_t tree, bool (*fn) (int,int)){
    if(tree_isEmpty(tree) || (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))))
        return true;
    else{
        bool left_true = false; bool right_true = false;
        if(!tree_isEmpty(tree_left(tree))){
            if(fn(tree_elt(tree), tree_elt(tree_left(tree))))
                left_true = tree_hasMonotonicPath_helper(tree_left(tree), fn);
        }
        if(!tree_isEmpty(tree_right(tree))){
            if(fn(tree_elt(tree), tree_elt(tree_right(tree))))
                right_true = tree_hasMonotonicPath_helper(tree_right(tree), fn);
        }
        return left_true || right_true;
    }
}
// helper for tree_hasMonotonicPath

bool tree_hasMonotonicPath(tree_t tree){
    if(tree_isEmpty(tree) || (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree)))){
        return false;
    }
    else{
        return tree_hasMonotonicPath_helper(tree,larger) || tree_hasMonotonicPath_helper(tree,smaller);
    }
}

// EFFECTS: Returns true if and only if "tree" has at least one
// root-to-leaf path such that all the elements along the
// path form a monotonically increasing or decreasing
// sequence.
//
// A root-to-leaf path is a sequence of elements in a tree
// starting with the root element and proceeding downward
// to a leaf (an element with no children).
//
// An empty tree has no root-to-leaf path.
//
// A monotonically increasing (decreasing) sequence is a
// sequence of numbers where no number is smaller (larger)
// than its previous number.


bool tree_allPathSumGreater(tree_t tree, int sum){
    if((sum-tree_elt(tree))<0)
        return true;
    else{
        if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
            return false;
        else{
            if(tree_isEmpty(tree_left(tree)))
                return tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
            if(tree_isEmpty(tree_right(tree)))
                return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree));
            return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree)) && tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
        }
    }
}
// REQUIRES: tree is not empty
//
// EFFECTS: Returns true if and only if for each root-to-leaf
// path of "tree", the sum of all elements along the path
// is greater than "sum".
//
// A root-to-leaf path is a sequence of elements in a tree
// starting with the root element and proceeding downward
// to a leaf (an element with no children).

bool covered_by(tree_t A, tree_t B){
    if(tree_isEmpty(A))
        return true;
    else{
        if(tree_isEmpty(B)){
            return false;
        }
        else{
            if(tree_elt(A) == tree_elt(B)){
                return covered_by(tree_left(A),tree_left(B)) && covered_by(tree_right(A),tree_right(B));
            }
            return false;
        }
    }
}
// EFFECTS: Returns true if tree A is covered by tree B.


bool contained_by(tree_t A, tree_t B){
    if(covered_by(A,B)){
        return true;
    }
    else{
        return contained_by(A,tree_left(B)) || contained_by(A,tree_right(B));
    }
}
// EFFECTS: Returns true if tree A is covered by tree B
// or a subtree of B.


tree_t insert_tree(int elt, tree_t tree){
    if(tree_isEmpty(tree)){
        return tree_make(elt,tree_make(),tree_make());
    }
    else if(elt<tree_elt(tree)){
        return tree_make(tree_elt(tree),insert_tree(elt, tree_left(tree)),tree_right(tree));
    }
    else {
        return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt, tree_right(tree)));
    }
}
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted as a leaf such that 
// the resulting tree is also a sorted binary tree.
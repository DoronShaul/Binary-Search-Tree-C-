/**
 * Examples of automatic tests for the exercise on binary trees.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
using std::cout, std::endl;

#include "badkan.hpp"
#include "Tree.hpp"

int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree;  
  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);
  
  ariel::Tree mytree;  
  ariel::Tree leftTree;
  ariel::Tree rightTree;


  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
 .CHECK_EQUAL (emptytree.size(), 1)
 .CHECK_EQUAL (emptytree.contains(5), true)
 .CHECK_OK    (emptytree.remove(5))
  .CHECK_EQUAL (emptytree.contains(5), false)
  .CHECK_THROWS(emptytree.remove(5))
 .CHECK_EQUAL (emptytree.size() ,0)
  
   .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_THROWS(threetree.left(6))
  .CHECK_OK    (threetree.print())
   
   //our test
  .CHECK_OK (mytree.insert(2))
   .CHECK_OK (mytree.insert(10))
  . CHECK_OK (mytree.insert(5))
  . CHECK_OK (mytree.insert(7))
  .CHECK_OK (mytree.insert(3))
  .CHECK_EQUAL (mytree.size(), 5)
  .CHECK_OK    (mytree.remove(10))
  .CHECK_EQUAL(mytree.root(), 2)
  .CHECK_EQUAL (mytree.right(2),7)
   .CHECK_EQUAL (mytree.parent(7), 2)
  .CHECK_THROWS(mytree.parent(2))
  .CHECK_THROWS(mytree.right(3))
  .CHECK_OK (mytree.insert(1))
  .CHECK_OK    (mytree.remove(2))
  .CHECK_EQUAL(mytree.root(), 1)
  .CHECK_THROWS(mytree.parent(1))
  .CHECK_OK  (mytree.print())
  .CHECK_THROWS(mytree.insert(3))
  . CHECK_OK (mytree.insert(9))
  . CHECK_OK (mytree.insert(11))
  . CHECK_OK (mytree.insert(10))
  .CHECK_OK    (mytree.remove(11))
  .CHECK_EQUAL (mytree.parent(10), 9)
  .CHECK_THROWS (mytree.right(10))
  .CHECK_EQUAL (mytree.right(9),10)

  .CHECK_OK    (leftTree.insert(10))
  .CHECK_OK    (leftTree.insert(9))
  .CHECK_OK    (leftTree.insert(8))
  .CHECK_OK    (leftTree.insert(7))
  .CHECK_OK    (leftTree.insert(6))
  .CHECK_OK    (leftTree.remove(8))
  .CHECK_EQUAL (leftTree.parent(7), 9)
  .CHECK_EQUAL (leftTree.left(9),7)

  .CHECK_OK    (rightTree.insert(10))
  .CHECK_OK    (rightTree.insert(11))
  .CHECK_OK    (rightTree.insert(12))
  .CHECK_OK    (rightTree.insert(13))
  .CHECK_OK    (rightTree.insert(14))
  .CHECK_OK    (rightTree.remove(13))
  .CHECK_EQUAL (rightTree.parent(14), 12)
  .CHECK_EQUAL (rightTree.right(12),14)
  .CHECK_EQUAL (rightTree.parent(12), 11)


  

  .print();

 


  
  
  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
  
}
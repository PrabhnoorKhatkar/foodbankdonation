#ifndef FOODBANKLIST_H
#define FOODBANKLIST_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "helperfunctions.h"


class NodeFoodBank {
private:
    std::string name;
    double totalReceived;
    std::string zipCode;
    NodeFoodBank* next = nullptr;
    NodeFoodBank* prev = nullptr;
public:
   //mutator function to add to the variable total receieved
    void addDonation(double donation);

    friend class FoodBankList;
};

class FoodBankList {
private:
    NodeFoodBank* head = nullptr;
    NodeFoodBank* tail = nullptr;

public:
    //function to add node to front of the linked list
    void addFront(std::string bankName, double totalReceived);
    //function to add node to end of the linked list
    void addEnd(std::string bankName, double totalReceived);
    //function to add node in the correct order
    void addInOrder(std::string bankName, double totalReceived, std::string zipCode);
    //function to print linked list
    void print();
    //function to mutate one of the nodes in the linked list
    void addToList(std::string name, double totalReceieved);
    //function to deallocate linked list.
    void deallocateList();


    friend class NodeFoodBank;
};


int hash_codeTwo(const std::string& key);

class HashTableTwo;
class IteratorHashTwo;

class NodeHashTwo
{
private:
   std::string key;
   double value;
   NodeHashTwo* next;
   

public:

   NodeHashTwo();
   double getTotal() const;
   void addToTotal(double amount);

friend class HashTableTwo;
friend class IteratorHashTwo;
};

class IteratorHashTwo
{
public:
   /**  
      Looks up the value at a position.
      @return the value of the node to which the iterator points
   */
   double get() const;
   int getIndex() const;
   void next();
   
   
   /**
      Compares two iterators.
      @param other the iterator to compare with this iterator
      @return true if this iterator and other are equal
   */
   bool equals(const IteratorHashTwo& other) const;
   
private:
   const HashTableTwo* container;
   int bucket_index;
   NodeHashTwo* current;
   
friend class HashTableTwo;
};


class HashTableTwo
{
public:
   /**
      Constructs a hash table.
      @param nbuckets the number of buckets
   */
   HashTableTwo(int nbuckets);
   /**
      Tests for set membership.
      @param x the potential element to test
      @return 1 if x is an element of this set, 0 otherwise
   */
   int count(const std::string& zipCode,double value);
   /**
      Adds an element to this hash table if it is not already present.
      @param x the element to add
   */
   void insert(const std::string& key, double value);
   /**
      Removes an element from this hash table if it is present.
      @param x the potential element to remove
   */
   
   /**
      Returns an iterator to the beginning of this hash table.
      @return a hash table iterator to the beginning
   */
   IteratorHashTwo begin() const;
   /**
      Returns an iterator past the end of this hash table.
      @return a hash table iterator past the end
   */
   IteratorHashTwo end() const;

   /**
      Gets the number of elements in this set.
      @return the number of elements
   */
   int size() const;
   /**
      Gets index of bucket from key
      @return the index
   */
   int findIndex(std::string key);
   /**
      Gets value inside bucket
      @return value
   */
   std::string findValue(std::string key);
   /**
      function that builds hashtable based on cipher.txt
   */
   
   //function to build hashtable with all the foodbanks and their total onations
   void buildFoodBankHash();

   //this function would add the donations to specefic elements in the table
   void addToTable(std::string key, double amount);

   //this function created a linked list based on the hashtable
   void hashtableToLinkedList(FoodBankList &bank);

   

   /**
      function that traverses through bucket
      @return value associated with key
   */
   double traverseBucket(std::string key);

   void addDonation(std::string key, double amount);
   
   /**
      function that prints out all elements within bucket
   */
   void printBucket(std::string key);

   void deallocateHashtableTwo();

   void test();
   

private:
   std::vector<NodeHashTwo*> buckets;
   int current_size;   

friend class IteratorHashTwo;
};




#endif

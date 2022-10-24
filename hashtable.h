#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

/**
   Computes the hash code for a string.
   @param str a string
   @return the hash code
*/
int hash_code(const std::string& key);

class HashTable;
class IteratorHash;

class NodeHash
{
private:
   std::string key;
   std::string data;
   char lettering;
   NodeHash* next;

friend class HashTable;
friend class IteratorHash;
};

class IteratorHash
{
public:
   /**  
      Looks up the value at a position.
      @return the value of the node to which the iterator points
   */
   std::string get() const;
   int getIndex() const;
   void next();
   /**
      Compares two iterators.
      @param other the iterator to compare with this iterator
      @return true if this iterator and other are equal
   */
   bool equals(const IteratorHash& other) const;
   
private:
   const HashTable* container;
   int bucket_index;
   NodeHash* current;
   
friend class HashTable;
};


class HashTable
{
public:
   /**
      Constructs a hash table.
      @param nbuckets the number of buckets
   */
   HashTable(int nbuckets);
   /**
      Tests for set membership.
      @param x the potential element to test
      @return 1 if x is an element of this set, 0 otherwise
   */
   int count(const std::string& zipCode,std::string value);
   /**
      Adds an element to this hash table if it is not already present.
      @param x the element to add
   */
   void insert(const std::string& zipCode, std::string foodBankName, char lettering);
   /**
      Removes an element from this hash table if it is present.
      @param x the potential element to remove
   */
   void erase(const std::string& key, std::string value);
   /**
      Returns an iterator to the beginning of this hash table.
      @return a hash table iterator to the beginning
   */
   IteratorHash begin() const;
   /**
      Returns an iterator past the end of this hash table.
      @return a hash table iterator past the end
   */
   IteratorHash end() const;
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
      function that builds hashtable based on foodbanks.txt
   */
   void buildBasedOnTextFile();

  
   /**
      function that traverses through bucket
      @return value associated with key
   */
   std::string traverseBucket(std::string key);
   
   /**
      function that prints out all elements within bucket
   */
   void printBucket(std::string key);
   //function to deallocate hashtable
   void deallocateHashTableOne();
   

private:
   std::vector<NodeHash*> buckets;
   int current_size;   

friend class IteratorHash;
};


#endif
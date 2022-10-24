#ifndef STACK_H
#define STACK_H
#include <string>
#include <fstream>

class NodeStack
{
private:
   std::string name;
   std::string foodBank;
   std::string donationAmount;

   NodeStack* next;
friend class Stack;   
};


/**
   An implementation of a stack as a sequence of nodes.
*/
class Stack
{
public:   
   /** 
      Constructs an empty stack.
   */
   Stack();

   /**
      Adds an element to the top of the stack.
      @param element the element to add
   */
   void push(std::string name, std::string foodBank, std::string donationAmount);

   /**
      Yields the top element's name
      @return the top element
   */
   std::string topName() const;
   //yields top element's donation amount
   std::string topDonationAmount() const;
   //yields top elements food bank
   std::string topFoodBank() const;

   /**
      Removes the element from the top of the stack.
   */
   void pop();

   /**
      Yields the number of elements in this stack.
      @return the size
   */
   int size() const;
   //function to build stack based on donors.txt
   void buildBasedOnDonorsFile();
   //function that deallocates the stack
   void deallocateStack();
  
private:   
   NodeStack* first;
   int len;
};

#endif
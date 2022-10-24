#include "stack.h"
#include "helperfunctions.h"

Stack::Stack()
{  
   first = nullptr;
   len = 0;
}

void Stack::push(std::string name, std::string foodBank, std::string donationAmount)
{  
   NodeStack* new_node = new NodeStack;
   new_node->name = name;
   new_node->foodBank = foodBank;
   new_node->donationAmount=donationAmount;
   new_node->next = first;
   first = new_node;
   len++;
   //delete new_node;
}

std::string Stack::topName() const
{
   return first->name;
}

std::string Stack::topDonationAmount() const
{
   return first->donationAmount;
}

std::string Stack::topFoodBank() const
{
   return first->foodBank;
}

void Stack::pop()
{
   NodeStack* to_delete = first;
   first = first->next;
   delete to_delete;
   len--;
}

int Stack::size() const
{
   return len;
}

void Stack::buildBasedOnDonorsFile()
{
   std::string name;
   std::string foodBank;
   std::string donationAmount;
   std::string row;
   std::ifstream in;

   in.open("donors.txt");
   if(in.is_open()) 
   {
      while(std::getline(in,row)) 
      {
         name = "";
         foodBank = "";
         donationAmount = "";
         int firstIndex = firstDigitIndex(row);
         int lastIndex = lastDigitIndex(row);

         for(int i = 0; i < firstIndex; i++)
         {
            name += row[i];
         }
         for(int i = firstIndex; i <= lastIndex; i++)
         {
            donationAmount += row[i];
         }
         for(int i = lastIndex + 1; i < row.size(); i++)
         {
            foodBank += row[i];
         }
         this->push(name, foodBank, donationAmount);
   }
}
}

void Stack::deallocateStack() {
   for(int i=0;i<this->size();i++) {
      this->pop();
   }
}
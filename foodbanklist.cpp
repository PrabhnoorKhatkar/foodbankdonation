#include "foodbanklist.h"



int hash_codeTwo(const std::string& key)
{
   int h = 0;
   for(int i=0;i<key.size();i++) {
      h += key[i];
   }
   
   return h;
}

NodeHashTwo::NodeHashTwo() {
   this->key="";
   this->value=0;
}

void NodeHashTwo::addToTotal(double amount) {
   this->value += amount;
}

double::NodeHashTwo::getTotal() const {
   return value;
}

HashTableTwo::HashTableTwo(int nbuckets)
{
   for (int i = 0; i < nbuckets; i++)
   {
      buckets.push_back(nullptr);
      buckets[i]=nullptr;
   }
   current_size = 0;
}

int HashTableTwo::count(const std::string& key, double value)
{
   int h = hash_codeTwo(key);
   h = h % buckets.size();
   if (h < 0) { h = -h; }
      
   NodeHashTwo* current = buckets[h];
   while (current != nullptr)
   {
      if (current->value == value) { return 1; }
      current = current->next;
   }
   return 0;
}

void HashTableTwo::insert(const std::string& key, double value)
{
   int h = hash_codeTwo(key);
   h = h % buckets.size();
   if (h < 0) { h = -h; }
      
   NodeHashTwo* current = buckets[h];
   while (current != nullptr)
   {
      if (current-> value == value) { 
         return; 
      } else {
         current = current->next;
      }
   }
   NodeHashTwo* new_node = new NodeHashTwo;
   new_node->key=key;
   new_node->value = value;
   new_node->next = buckets[h];
   buckets[h] = new_node;
   current_size++;
}



int HashTableTwo::size() const
{
   return current_size;
}

IteratorHashTwo HashTableTwo::begin() const
{
   IteratorHashTwo iter;
   iter.current = nullptr;
   iter.bucket_index = -1;
   iter.container = this;
   //iter.next();
   return iter;
}

IteratorHashTwo HashTableTwo::end() const
{
   IteratorHashTwo iter;
   iter.current = nullptr;
   iter.bucket_index = buckets.size();
   iter.container = this;
   return iter;
}

int HashTableTwo::findIndex(std::string key) {
   int h = hash_codeTwo(key);
   h = h % buckets.size();
   if (h < 0) { h = -h; }

   return h;
}

void HashTableTwo::buildFoodBankHash() {
   std::string key;
   std::string row;
   std::string numberStr;
   std::ifstream in;
   int counter=0;
   in.open("donors.txt"); 
   if(in.is_open()) {
      while(std::getline(in, row)) {
         key="";
         numberStr="";
         int first=firstDigitIndex(row);
         int last=lastDigitIndex(row);
         for(int i=first;i<=last;i++) {
            numberStr+=row[i];
         }
         double amount=std::stod(numberStr);
         for(int i=last+2;i<row.size();i++) {
            key+=row[i];
         }
         

         int index=findIndex(key);
         NodeHashTwo* traverse=buckets[index];
         if(traverse == nullptr) {
            this->insert(key, amount);
         } else {
            while(traverse->key != key && traverse->next != nullptr) {
               traverse=traverse->next;
            }
            if(traverse->key == key) {
               traverse->addToTotal(amount);
            } else {
               this->insert(key, amount);
            }
         }
      }
      in.close();
  }
}

void HashTableTwo::addToTable(std::string key, double amount) {
   int index=findIndex(key);
   NodeHashTwo* traverse=buckets[index];
   if(traverse == nullptr) {
      this->insert(key, amount);
   } else {
      while(traverse->key != key && traverse->next != nullptr) {
         traverse=traverse->next;
      }
      if(traverse->key == key) {
         traverse->addToTotal(amount);
      } else {
         this->insert(key, amount);
      }
   }
}



double HashTableTwo::traverseBucket(std::string key) {
   int index=findIndex(key);
   NodeHashTwo* traverse=buckets[index];
   while(traverse->next != nullptr && traverse->key != key) {
      traverse=traverse->next;
   }

   return traverse->value;
}

void HashTableTwo::printBucket(std::string key) {
   int index=findIndex(key);
   NodeHashTwo* traverse=buckets[index];
   bool move=true;
   while(move) {
      if(traverse->key == key) {
         std::cout<<traverse->value<<std::endl;
      }
      if(traverse->next != nullptr) {
         traverse = traverse->next;
      } else {
         move=false;
      }
      
   }
}

void HashTableTwo::addDonation(std::string key, double amount) {
   int index=findIndex(key);
   NodeHashTwo* traverse=buckets[index];
   while(traverse->next != nullptr && traverse->key != key) {
      traverse=traverse->next;
   }
   
   traverse->value+=amount;
   
}

void HashTableTwo::hashtableToLinkedList(FoodBankList &bank) {
   std::string bankName;
   std::string number;
   std::string zipCode;
   std::string row;
   std::ifstream in;
   in.open("Foodbank.txt");
   if(in.is_open()) {
      while(getline(in,row)) {
         bankName="";
         zipCode="";
         int firstDigit=firstDigitIndex(row);
         for(int i=2;i<firstDigit-1;i++) {
            bankName += row[i];
         }
         for(int i=firstDigit;i<row.size();i++) {
            zipCode += row[i];
         }
         double amountReceived=this->traverseBucket(bankName);
         bank.addInOrder(bankName,amountReceived,zipCode);
      }
   }

}



void HashTableTwo::deallocateHashtableTwo() {
   
   for(int i=0;i<current_size;i++) {
      NodeHashTwo* traverse=buckets[i];
      if(buckets[i] != nullptr) {
         delete traverse;
         while(traverse->next != nullptr) {
            delete traverse;
            traverse=traverse->next;
         }
      }  
   } 
}

double IteratorHashTwo::get() const
{
   return current->value;
}

int IteratorHashTwo::getIndex() const {
   return bucket_index;
}

bool IteratorHashTwo::equals(const IteratorHashTwo& other) const
{
   return current == other.current;
}

void IteratorHashTwo::next()
{
   if (bucket_index >= 0 && current->next != nullptr)
   {
      current = current->next;
   }   
   else 
   {
      // Move to the next bucket
      do
      {
         bucket_index++;
      }
      while (bucket_index < container->buckets.size()
         && container->buckets[bucket_index] == nullptr);
      if (bucket_index < container->buckets.size())
      {
         // Start of next bucket
         current = container->buckets[bucket_index];         
      }
      else 
      {
         // No more buckets
         current = nullptr;
      }
   }
}







void NodeFoodBank::addDonation(double donation) {
    this->totalReceived += donation;
}

void FoodBankList::addFront(std::string bankName, double totalReceived) {
    NodeFoodBank* newNode=new NodeFoodBank();
    newNode->name=bankName;
    newNode->totalReceived=totalReceived;
    if(this->head==nullptr) {
        this->head=newNode;
        this->tail=newNode;
    } else {
        newNode->next=this->head; 
        this->head->prev=newNode;
        this->head=newNode;
    }
}

void FoodBankList::addEnd(std::string bankName, double totalReceived) {
    NodeFoodBank* newNode=new NodeFoodBank();
    newNode->name=bankName;
    newNode->totalReceived=totalReceived;
    if(this->head==nullptr) {
        this->head=newNode;
        this->tail=newNode;
    } else {
        newNode->prev=this->tail;
        this->tail->next=newNode;
        this->tail=newNode;
        newNode->next=nullptr;

    }
    
}



void FoodBankList::print() {
   
   NodeFoodBank* traverse=this->head;
   bool check=true;
   while(check) {
      //std::cout<<traverse->name<<"("<<traverse->zipCode<<")"<<": $"<<traverse->totalReceived<<std::endl;
      std::cout<<traverse->name<<": $"<<traverse->totalReceived<<std::endl;
      if(traverse->next != nullptr) {
         traverse=traverse->next;
      } else {
         check=false;
        }
   }
}

void FoodBankList::addInOrder(std::string bankName, double totalReceived,std::string zipCode) {
    NodeFoodBank* newNode=new NodeFoodBank();
    newNode->name=bankName;
    newNode->totalReceived=totalReceived;
    newNode->zipCode=zipCode;
    NodeFoodBank* traverse=this->head;
    if(this->head==nullptr) {
        this->head=newNode;
        this->tail=newNode;
    } else {
        if(newNode->totalReceived < head->totalReceived) {
            addFront(bankName,totalReceived);
        } else if(newNode->totalReceived > tail->totalReceived) {
            addEnd(bankName,totalReceived);
        } else {
            while(newNode->totalReceived > traverse->totalReceived && traverse->next != nullptr) {
                traverse=traverse->next;
            }
            newNode->next=traverse;
            newNode->prev=traverse->prev;
            traverse->prev->next=newNode;
            traverse->prev=newNode;
        }
    }
}

void FoodBankList::deallocateList() {
   NodeFoodBank* traverse=this->head;
   while(traverse->next != nullptr) {
      delete traverse;
      traverse=traverse->next;
   }
}

void FoodBankList::addToList(std::string name, double totalRecieved) {
   NodeFoodBank* traverse=this->head;
   bool check = true;
   while(check) {
      if(traverse->name == name) {
         traverse->addDonation(totalRecieved);
         check = false;
      }
      if(traverse->next != nullptr) {
         traverse = traverse->next;
      } else {
         check = false;
      }
      
   }
}

void HashTableTwo::test() {
   NodeHashTwo* traverse=buckets[0];
   if(traverse == nullptr) {
      std::cout<<"This is null";
   }
   
}
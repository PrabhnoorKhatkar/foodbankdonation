#include "hashtable.h"
#include "helperfunctions.h"

int hash_code(const std::string &key)
{
   int h = 0;
   for (int i = 0; i < key.size(); i++)
   {
      h += key[i];
   }

   return h;
}

HashTable::HashTable(int nbuckets)
{
   for (int i = 0; i < nbuckets; i++)
   {
      buckets.push_back(nullptr);
   }
   current_size = 0;
}

int HashTable::count(const std::string &key, std::string value)
{
   int h = hash_code(key);
   h = h % buckets.size();
   if (h < 0)
   {
      h = -h;
   }

   NodeHash *current = buckets[h];
   while (current != nullptr)
   {
      if (current->data == value)
      {
         return 1;
      }
      current = current->next;
   }
   return 0;
}

void HashTable::insert(const std::string &key, std::string value, char letter)
{
   int h = hash_code(key);
   h = h % buckets.size();
   if (h < 0)
   {
      h = -h;
   }

   NodeHash *current = buckets[h];
   while (current != nullptr)
   {
      if (current->data == value)
      {
         return;
      }
      else
      {
         current = current->next;
      }
   }
   NodeHash *new_node = new NodeHash;
   new_node->key = key;
   new_node->data = value;
   new_node->lettering = letter;
   new_node->next = buckets[h];
   buckets[h] = new_node;
   current_size++;
}

void HashTable::erase(const std::string &key, std::string value)
{
   int h = hash_code(key);
   h = h % buckets.size();
   if (h < 0)
   {
      h = -h;
   }

   NodeHash *current = buckets[h];
   NodeHash *previous = nullptr;
   while (current != nullptr)
   {
      if (current->data == value)
      {
         if (previous == nullptr)
         {
            buckets[h] = current->next;
         }
         else
         {
            previous->next = current->next;
         }
         delete current;
         current_size--;
         return;
      }
      previous = current;
      current = current->next;
   }
}

int HashTable::size() const
{
   return current_size;
}

IteratorHash HashTable::begin() const
{
   IteratorHash iter;
   iter.current = nullptr;
   iter.bucket_index = -1;
   iter.container = this;
   iter.next();
   return iter;
}

IteratorHash HashTable::end() const
{
   IteratorHash iter;
   iter.current = nullptr;
   iter.bucket_index = buckets.size();
   iter.container = this;
   return iter;
}

int HashTable::findIndex(std::string key)
{
   int h = hash_code(key);
   h = h % buckets.size();
   if (h < 0)
   {
      h = -h;
   }

   return h;
}

std::string HashTable::findValue(std::string key)
{
   int h = hash_code(key);
   h = h % buckets.size();
   if (h < 0)
   {
      h = -h;
   }

   std::string find = "";
   for (IteratorHash iter = this->begin(); !iter.equals(this->end()); iter.next())
   {
      if (h == iter.getIndex())
      {
         find = iter.get();
      }
   }
   return find;
}

void HashTable::buildBasedOnTextFile()
{
   std::string key;
   std::string foodBankName;
   char letter;
   std::string row;
   std::ifstream in;

   in.open("Foodbank.txt");
   if (in.is_open())
   {
      while (std::getline(in, row))
      {
         letter = row[0];
         key = "";
         foodBankName = "";
         int first = firstDigitIndex(row);
         for (int i = 2; i < first - 1; i++)
         {
            foodBankName += row[i];
         }
         for (int i = first; i < row.size(); i++)
         {
            key += row[i];
         }

         this->insert(key, foodBankName, letter);
      }
   }
}

std::string HashTable::traverseBucket(std::string key)
{
   int index = findIndex(key);
   NodeHash *traverse = buckets[index];
   while (traverse->next != nullptr && traverse->key != key)
   {
      traverse = traverse->next;
   }

   return traverse->data;
}

void HashTable::printBucket(std::string key)
{
   int index = findIndex(key);
   NodeHash *traverse = buckets[index];
   bool move = true;
   while (move) {
      if (traverse->key == key) {
         std::cout << traverse->lettering << ")-" << traverse->data << std::endl;
      } if (traverse->next != nullptr) {
         traverse = traverse->next;
      } else {
         move = false;
      }
   }
}

   void HashTable::deallocateHashTableOne() {
   
   for(int i=0;i<current_size;i++) {
      NodeHash* traverse=buckets[i];
      NodeHash* deleteHash=traverse;
      if(buckets[i] != nullptr) {
         traverse=traverse->next;
         delete deleteHash;
         while(traverse != nullptr) {
            NodeHash* deleteHash=traverse;
            traverse=traverse->next;
            delete deleteHash;
         }
      }  
   } 
}

   


   std::string IteratorHash::get() const
   {
      return current->data;
   }

   int IteratorHash::getIndex() const
   {
      return bucket_index;
   }

   bool IteratorHash::equals(const IteratorHash &other) const
   {
      return current == other.current;
   }

   void IteratorHash::next()
   {
      if (bucket_index >= 0 && current->next != nullptr)
      {
         // Advance in the same bucket
         current = current->next;
      }
      else
      {
         // Move to the next bucket
         do
         {
            bucket_index++;
         } while (bucket_index < container->buckets.size() && container->buckets[bucket_index] == nullptr);
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

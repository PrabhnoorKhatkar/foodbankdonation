#include "priorityqueue.h"
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "helperfunctions.h"


DonorPQNode::DonorPQNode(std::string name, std::string foodBank, double donationAmount)
{

   this->name = name;
   this->foodBank = foodBank;
   this-> donationAmount = donationAmount;

}

void addDonorPQ(std::priority_queue<DonorPQNode> PQqueue, std::string name, std::string foodBank, double donationAmount)
{

PQqueue.push(DonorPQNode(name, foodBank, donationAmount));

}

double DonorPQNode::get_donation() const
{ 
    return donationAmount; 
}

std::string DonorPQNode::get_name() const
{ 
    return name; 
}
std::string DonorPQNode::get_foodbank() const
{ 
    return foodBank; 
}

bool operator <(const DonorPQNode& a, const DonorPQNode& b)
{

return a.get_donation() < b.get_donation();

}


void buildBasedOnDonorsFilePQ(std::priority_queue<DonorPQNode> PQqueue)
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

       double amount = std::stod(donationAmount);
       PQqueue.push(DonorPQNode(name, foodBank, amount));
   }

}

     DonorPQNode important = PQqueue.top();
     std::cout <<"Top Donor: "<<std::endl;
     std::cout<< important.get_name()<<": $"<<important.get_donation()<< std::endl;
         
}

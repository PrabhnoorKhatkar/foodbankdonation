#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <queue>
#include <string>

class DonorPQNode
{
public:

DonorPQNode(std::string name, std::string foodBank, double donationAmount); // Constructor

 double get_donation() const;
 std::string get_name() const;
 std::string get_foodbank() const;

private:

   std::string name;
   std::string foodBank;
   double donationAmount;
   
   friend class PriorityQueue;
};
//function that builds priority queue based on donors.txt
void buildBasedOnDonorsFilePQ(std::priority_queue<DonorPQNode> PQqueue);
//function that adds element to priority queue
void addDonorPQ(std::priority_queue<DonorPQNode> PQqueue, std::string name, std::string foodBank, double donationAmount);
bool operator <(const DonorPQNode& a, const DonorPQNode& b);


#endif


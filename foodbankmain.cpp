#include <iostream>
#include <string>
#include <vector>
#include "hashtable.h"
#include "binarytree.h"
#include "stack.h"
#include "foodbanklist.h"
#include "helperfunctions.h"
#include "priorityqueue.h"


int main() {
    
    
    
    
    std::cout << "\nHello, this program serves as a tool for you to be able to donate to any"<<
    " food bank of your choice within the tri-city area. Would you like to check it out? (y/n)";
    char responseEnter;
    bool validDonation = true;
    

    int existSize = 9;
    int usedSize = 6;
    //defining the arrays that contain the zipcdes in the tricity and the zipcodes within our program
    int zipCodesExist[9] = {94536,94537,94538,94539,94555,94560,94544,94552,94587};
    int zipCodesUsed[6] = {94536,94537,94538,94555,94560,94587};
    bool validAnonymous = true;
    std::string userName = "Anonymous";
    char responseAnonymous;
    bool checkForSurvey = false;

    //defining the stack and calling function to build it
    Stack recentDonor;
    recentDonor.buildBasedOnDonorsFile();
    //defining the hashtable for zipcodes and calling function to build it
    HashTable table1(13);
    table1.buildBasedOnTextFile();
    //defining list that will be ordered with the foodbanks based on donations received
    FoodBankList bankList;
    //defining the hashtable for foodbanks with donation amount
    HashTableTwo table2(15);
    //building the hashtable and linked list
    table2.buildFoodBankHash();
    table2.hashtableToLinkedList(bankList);

    while(validDonation) {
        std::cin >> responseEnter;
        if(responseEnter == 'y') {
            checkForSurvey = true;
            std::cout << "Would you like to remain anonymous? (y/n)";
            while(validAnonymous) {
                std::cin >> responseAnonymous;
                std::cin.ignore();
                if(responseAnonymous == 'y') {
                    validAnonymous = false;
                } else if(responseAnonymous == 'n') {
                    std::cout << "Enter your name: ";
                    std::getline(std::cin,userName);
                    validAnonymous = false;
                } else {
                    std::cout<< "Please enter a valid response: ";
                }   
            }
            //Defining priority queue for the top donator
            std::priority_queue<DonorPQNode> topDonator; 
            //printing out the most recent donor
            std::cout<<"\n\nMost recent donor: "<<std::endl;
            std::cout<<recentDonor.topName()<<": $"<<recentDonor.topDonationAmount()<<std::endl;
            std::cout<<std::endl;
            //printing out top donor
            buildBasedOnDonorsFilePQ(topDonator);
            //printing out list of food banks with donation receieved
            std::cout<<"\nList of Food Banks with the Total Donation they Recieved: "<<std::endl;
            bankList.print();
            //asks user for zipcode
            bool validZipCode = false;
            std::cout<<"\nEnter a zipcode that you would like to find a foodbank in: ";
            std::string zipCode;
            //validates the zipcode entered by user to make sure that it is covered in our program
            while(!validZipCode) {
                std::cin>>zipCode;
                int realZip=std::stoi(zipCode);
                int functionToValidify = validifyZipcode(realZip,zipCodesUsed,zipCodesExist,6,9);
                if(functionToValidify == 1) {
                    validZipCode = true;
                } else if(functionToValidify == 2) {
                    std::cout<<"There are no foodbanks registered in this zip code. Try Another: ";
                } else if(functionToValidify == 0) {
                    std::cout<<"This program does not extend to this zipcode. Please Reenter: ";
                }

            }
            //listing out the foodbanks in the users zipcode of choice
            bool donate=false;
            char letter;
            char donateOrNot;
            while(!donate) {
                //allows user to select food bank
                std::cout<<"\n\nWhich food bank would you like to select(Enter the letter next to the food bank)? ";
                std::cout<<"\n\nThese are the foodbank(s) in the zipcode "<<zipCode<<":"<<std::endl;
                //prints out foodbanks within zipcode of choice
                table1.printBucket(zipCode);
                std::cout<<std::endl;
                //allows user to select food bank by inputting letter
                std::cout<<"Enter Here: ";
                std::cin>>letter;
                char newLetter=toupper(letter);
                std::cout<<std::endl;
                //fucntion to return name of bank based on the letter passed into it
                std::string foodBankName=getNameFromLetter(newLetter);
                //function to print out paragraph about the selected food banks
                printOutBankDescription(newLetter);
                std::cout<<"\n\nWould you like to donate to this foodbank? (y/n): ";
                std::cin>>donateOrNot;
                //input validation for their response on whether they want to donate
                if(donateOrNot == 'Y' || donateOrNot == 'y') {
                    std::cout<<"How much would you like to donate?: ";
                    double amountToDonate;
                    std::cin>>amountToDonate;
                    std::cout<<"\n*Thank you for yor donation to the "<<foodBankName<<"!*"<<std::endl;
                    std::string donationAmount=std::to_string(amountToDonate);
                    appendDonation(userName,donationAmount,foodBankName);

                    //pushing user's donation to the data structures
                    recentDonor.push(userName, foodBankName, donationAmount);
                    table1.insert(zipCode,foodBankName,newLetter);
                    bankList.addToList(foodBankName, amountToDonate);
                    std::cout<<"\n\nMost recent donor: "<<std::endl;
                    std::cout<<recentDonor.topName()<<": $"<<recentDonor.topDonationAmount()<<std::endl;
                    std::cout<<std::endl;
                    buildBasedOnDonorsFilePQ(topDonator);
                    std::cout<<"\nList of Food Banks with the Total Donation they Recieved: "<<std::endl;
                    bankList.print();


                    donate=true;
                } else if(donateOrNot == 'N' || donateOrNot == 'n') {
                    continue;
                } else {
                    std::cout<<"Invalid Response. Please Re-enter: ";
                }
    
            }
            std::cout<<"\nWould you like to make another donation? (y/n) ";

            // std::cout<<std::endl;
        } else if(responseEnter == 'n') {
            std::cout << "Have a good day " << userName << "!";
            validDonation = false;
        } else {
            std::cout <<"Please enter a valid response: ";
        }
    }
    std::cout<<std::endl<<std::endl;
    //checks to see if user tried out our program. If they did, they would be asked to do a survey
    if(checkForSurvey) {
        char choiceForSurvey;
        std::cout << "Do you have a minute to spare for quick survey?" << std::endl;
        std::cout << "Enter yes or no (y/n): ";
        while(checkForSurvey) {
            std::cin >> choiceForSurvey;
            if(choiceForSurvey == 'Y' || choiceForSurvey == 'y') {
                survey();
                checkForSurvey = false;
            } else if(choiceForSurvey == 'N' || choiceForSurvey == 'n') {
                std::cout<<"Ok, have a great day!"<<std::endl;
                checkForSurvey = false;
            } else {
                std::cout<<"Invalid Response. Please Reenter(y/n): ";
            }
        }
        
        
    }
    
    
    
    
    // FoodBankList bankList;
    // HashTableTwo table2(15);
    // table2.buildFoodBankHash();
    // table2.hashtableToLinkedList(bankList);
    // //bankList.print();
    
    

    return 0;
}

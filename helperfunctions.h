#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//function to find index of first digit in string
int firstDigitIndex(std::string row); 
//function to find index of last digit in string
int lastDigitIndex(std::string row);
//function to find index of first colon in string
int indexOfColon(std::string row);
//function that prints out the description of the food banks
void printOutBankDescription(char letter);
//function that determines the food bank associated with the letter passed into the function
std::string getNameFromLetter(char letter);
//function that adds a donation to the donors.txt file
void appendDonation(std::string name,std::string amount, std::string foodBank);
// fucntion that ensures that the user entered a correct zip code
int validifyZipcode(int input, int zipCodeUsed[], int zipCodeExist[], int usedSize, int existSize); 

#endif

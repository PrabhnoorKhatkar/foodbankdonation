#include "helperfunctions.h"

int firstDigitIndex(std::string row)
{
    for (int i = 0; i < row.size(); i++)
    {
        if (isdigit(row[i]))
        {
            return i;
        }
    }
    return -1;
}

int lastDigitIndex(std::string row)
{
    int index;
    for (int i = 0; i < row.size(); i++)
    {
        if (isdigit(row[i]))
        {
            index = i;
        }
    }
    return index;
}

int indexOfColon(std::string row)
{
    int index;
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] == ':')
        {
            return i;
        }
    }
    return -1;
}

void printOutBankDescription(char letter)
{
    std::string row;
    std::ifstream in;
    in.open("foodbankdescription.txt");
    if (in.is_open())
    {
        while (std::getline(in, row))
        {
            if (row[0] == letter)
            {
                int index = indexOfColon(row);
                for (int i = index + 1; i < row.size(); i++)
                {
                    std::cout << row[i];
                }
            }
        }
        in.close();
    }
}

std::string getNameFromLetter(char letter)
{
    std::string name;
    std::string row;
    std::ifstream in;
    in.open("Foodbank.txt");
    if (in.is_open())
    {
        while (std::getline(in, row))
        {
            if (row[0] == letter)
            {
                int index = firstDigitIndex(row);
                for (int i = 2; i < index - 1; i++)
                {
                    name += row[i];
                }
            }
        }
        in.close();
    }
    return name;
}
// apending to text file
void appendDonation(std::string name, std::string amount, std::string foodBank)
{
    std::ofstream out;
    out.open("donors.txt", std::ios::app);
    if (out.is_open())
    {
        out << std::endl
            << name << " " << amount << " " << foodBank;
        out.close();
    }
}

int validifyZipcode(int input, int zipCodeUsed[], int zipCodeExist[], int usedSize, int existSize) {
    int exist = 0;
    int used = 0;
    for(int i = 0;i<existSize;i++) {
        if(input == zipCodeExist[i]) {
            exist = 1;
        }
    }

    for(int i = 0;i<usedSize;i++) {
        if(input == zipCodeUsed[i]) {
            used = 1;
        }
    }

    if(exist == 1 && used == 1) {
        return 1;
    } else if(exist == 1 && used == 0) {
        return 2;
    } else {
        return 0;
    }
}
#include "binarytree.h"

void survey()
{
    char again;
    struct treenode* root = new treenode("Are you happy with donation experience?");
        
    //Left side of tree
    struct treenode* curr = root;
    root->left = new treenode("Great do you have any constructive critiscm?");
    root->left->left = new treenode("Any feedback is good feedback. Let us know what is on your mind about our program");
    //root->left->right = new treenode("Thank you for your time");

    //Right side of tree
    root->right = new treenode("Was there a problem donating?");
    root->right->left = new treenode("Did you make an donation amount error while donating?");
    root->right->left->left = new treenode("Enter your corrected information including Name Amount and Food Bank when prompted");
    root->right->left->right = new treenode("Did you make a wrong foodbank selection?");
    root->right->left->right->left = new treenode("Enter your corrected information including Name Amount and Food Bank when prompted");
    root->right->left->right->right = new treenode("Did you make an error entering your name?");
    root->right->left->right->right->left = new treenode("Enter your corrected information including Name Amount and Food Bank when prompted");

    root->right->right = new treenode("Was there a problem in finding a foodbank?");
    root->right->right->right = new treenode("Great do you have any negative critiscm?");
    root->right->right->right->left =  new treenode("All feedback is good feedback. Let us know what is on your mind about our program");
    root->right->right->left = new treenode("Was there an missing/incorrect/error you know of in a foodbank option?");
    root->right->right->left->left = new treenode("Which foodbank?");
    root->right->right->left->right = new treenode("Were there no foodbanks in your area?");
    root->right->right->left->right->left = new treenode("Enter your zipcode when prompted");

    do
    {
            
        curr = root;
          
        bool done = false;
       
        while (!done)
        {
            std::cout << curr->data << " Enter y/n to continue: ";
            char choice;
            std::cin >> choice;
            while (choice != 'y' && choice != 'n') // Input Validation
            {
                std::cout << "Please enter y/n: ";
                std::cin >> choice;
            }
            if (choice == 'y' && curr->left != NULL)
            {
                curr=curr->left;
            }
            else if (choice == 'n' && curr->right != NULL)
            {
                curr=curr->right;     
            }
            else if(choice == 'n' && curr->right == NULL) 
            {
                done = true;
            }
            else if(choice == 'y' && curr->left == NULL)
            {
                std::string message = getUserMessage();
                recordUserMessage(message);
                done = true;
            } 
        }
        std::cout << "Thank you for your time" << std::endl;
            
        again = 'n';
        curr = root;
    } while (again == 'y');
    deleteTree(root); // Deallocate the tree
}
       
    


std::string getUserMessage()
{
    std::string userMessage;
    std::cout << "Enter your concern/message: ";
    std::cin.ignore();
    std::getline(std::cin, userMessage);
    return userMessage;
}

void recordUserMessage(std::string userMessage)
{
    std::ofstream outfile;
    outfile.open("UserResponses.txt", std::ios::app);  // opens file in append mode, previous contents saved
    outfile << userMessage << std::endl;
}

void deleteTree(treenode* root)
{
    if(root == NULL)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
#include "./Category/Category.h"
#include "./GradePredictor/GradePredictor.h"
#include <vector>
#include<ios>
#include<limits> 
using namespace std;










int main(){


GradePredictor predictor;
Category category;

vector<Category> categories = predictor.readFromFile("GradeBook.txt");

char choice;

do {
predictor.clearScreen();
predictor.printCategorySummary(categories);

string name = predictor.getCategoryName(categories);
predictor.printCategoryDetails(categories, name);

predictor.editAssignment(categories);
cout << "press enter to see new category report ";
cin.get();
predictor.clearScreen();
predictor.printCategoryDetails(categories,name);
predictor.editAssignment(categories);
cout << "press enter to see new category report ";
cin.get();

predictor.clearScreen();
predictor.printCategorySummary(categories);

cout << "Do you want to see a new category report? (Y/N)";
cin>> choice;
cin.ignore();

} while(choice == 'y' || choice == 'Y');





  return 0;
}
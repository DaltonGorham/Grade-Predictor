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

predictor.printCategorySummary(categories);

string name = predictor.getCategoryName(categories);
predictor.printCategoryDetails(categories, name);

predictor.editAssignment(categories);

predictor.printCategoryDetails(categories,name);
cout << "press enter to continue ";
cin.get();

predictor.printCategorySummary(categories);








  return 0;
}
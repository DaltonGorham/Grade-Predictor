#include "./Category/Category.h"
#include "./GradePredictor/GradePredictor.h"
#include <vector>
using namespace std;
void editAndUpdateAssignments(GradePredictor& predictor, vector<Category>& categories);
void showCategoryDetails(GradePredictor& predictor, vector<Category>& categories, string& name);
void showCategorySummary(GradePredictor& predictor, vector<Category>& categories);



int main(){

  GradePredictor predictor;
  vector<Category> categories = predictor.readFromFile("GradeBook.txt");

  char choice;
  string categoryName;
  double overallGrade = predictor.calculateOverallGrade(categories);

  do {
      showCategorySummary(predictor, categories);
      cout << "Predicted Grade for the Class: " << overallGrade << "%" << endl;

      categoryName = predictor.getCategoryName(categories);
      showCategoryDetails(predictor, categories, categoryName);

      do {
          editAndUpdateAssignments(predictor, categories);
          showCategoryDetails(predictor, categories, categoryName);
          cout << "Do you want to edit another assignment in this Category? (Y/N): ";
          cin >> choice;
          cin.ignore(); 
      } while (choice == 'y' || choice == 'Y');

      showCategorySummary(predictor, categories);

     
      cout << "Predicted Grade for the Class: " << overallGrade << "%" << endl;

      cout << "Do you want to see a new category report? (Y/N): ";
      cin >> choice;
      cin.ignore(); 

    } while (choice == 'y' || choice == 'Y');


  return 0;
}







void editAndUpdateAssignments(GradePredictor& predictor, vector<Category>& categories) {
  predictor.editAssignment(categories);
}

void showCategoryDetails(GradePredictor& predictor, vector<Category>& categories, string& name) {
  predictor.clearScreen();
  predictor.printCategoryDetails(categories, name);
  cout << "Press Enter to continue...";
  cin.get();
}

void showCategorySummary(GradePredictor& predictor, vector<Category>& categories) {
  predictor.clearScreen();
  predictor.printCategorySummary(categories);
}
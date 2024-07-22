#include "./Category/Category.h"
#include "./GradePredictor/GradePredictor.h"
#include <vector>
using namespace std;










int main(){


GradePredictor predictor;
Category category;

vector<Category> categories = predictor.readFromFile("GradeBook.txt");

predictor.printCategory(categories);




  return 0;
}
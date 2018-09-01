// Definition of class GradeBook that finds the maximum of three grades.
// Member functions are defined in GradeBook.cpp
#include <string>
using namespace std;

// GradeBook class definition
class GradeBook
{
public:
    GradeBook(string); // constructor initializes course name
    void setCourseName(string); // fucntion to set the course name
    string getCourseName(); // function to retrive to course name
    void displayMessage();  // display a welcome message
    void inputGrades(); // input three grades from user
    void displayGradeReport();  // display a report based on the grades
    int maximum(int, int, int); // determine max of 3 values
    // void maximum(int, int, int);

private:
    string courseName;  // course name for this GradeBook
    int maximumGrade;   // maximum of three grades
};


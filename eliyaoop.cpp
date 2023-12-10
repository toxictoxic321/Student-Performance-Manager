#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

class course; 
class student {
    friend class course;
    friend class userinput;
    string courses[5];             // Use an array to store courses
    int limit;                     // a student can only take 5 courses only.
    string attend[31][6];            //attendence for the month of november of each subject
    string marks[5][6];                //stores marks of each student
public:
    string studentname, uni;
    int rollno;
    student() {
       
    }
    student(string a, int b,string c) {
        studentname = a;
        rollno = b;
        uni = c;
        for (int i = 0; i < 5; ++i) {
            courses[i] = "null";
        }
        limit = 5;
        
        for (int i = 0; i < 31; ++i) {
            for (int j = 0; j < 6; ++j) {
                attend[i][j] = "";
            }
        }
        for (int i = 1;i < 31;++i) {                                                  //assigning days  from 1 till 30in the attendence of student
            attend[i][0] = "day" + to_string(i);

        }
    
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 6; ++j) {
                marks[i][j] = "";
            }
        }
        marks[1][0] = "assignment";
        marks[2][0] = "quiz";
        marks[3][0] = "midexam";
        marks[4][0] = "finalexam";
    
    }

    void studentdisplay() {
        int a = 0;
        cout << "student name is = " << studentname << endl;
        cout << "student uni is = " << uni << endl;
        cout << "student roll no is = " << rollno << endl;
        cout << "limit is = " << limit << endl;
        cout << "courses taken are : " << endl;
        for (int i = 0; i < 5; ++i) {
            if (courses[i] != "null") {
                a = 1;
                cout << courses[i] << endl;
            }
        }
        if (a == 0) {
            cout << "NONE." << endl;
        }
    }

    void studentedit(string a, bool c) {                      //to add or remove courses from student
        if (c==1) { 
            if (limit != 0) {
                for (int i = 0; i < 5; ++i) {
                    if (courses[i] == "null") {
                        courses[i] = a;
                        limit -= 1;
                        for (int j = 1;j < 6;++j) {
                            if (attend[0][j] == "") {
                                attend[0][j] = courses[i];
                                break;
                            }
                        }
                        for (int j = 1;j < 6;++j) {
                            if (marks[0][j] == "") {
                                marks[0][j] = courses[i];
                            }
                            break;
                        }


                        break;
                    }
                }
            }
            else {
                cout << "the student " << studentname << " has taken already 5 courses" << endl;
            }
        }
        else {
            bool found;
            for (int i = 0; i < 5; ++i) {
                if (courses[i] == a) {
                    courses[i] = "null";
                    limit += 1;
                    for (int j = 1;j < 6;++j) {
                        if (attend[0][j] == a) {
                            attend[0][j] = "";
                            
                            for (int k = 1;k < 31;++k) {                 //to finish the attencdence of deleted course.
                                attend[k][j] = "";
                            }
                            break;
                        }
                    }

                    for (int j = 1;j < 6;++j) {
                        if (marks[0][j] == a) {
                            marks[0][j] = "";

                            for (int k = 1;k < 5;++k) {                 //to finish the marks of deleted course.
                                marks[k][j] = "";
                            }
                            break;
                        }
                    }


                    found = true;
                    break;
                }
            }
            if (found==true) {
                cout << "student does not take this course" << endl;
            }
        }
    }

    void attenddisplay() {                   //student attendence display 
        system("cls");
        for (int i = 0;i < 31;++i) {
            
            for (int j = 0;j < 6;++j) {
                    cout << attend[i][j]<<"    ";
                }
            cout << endl;
        }

    }

    void marksdisplay() {
        system("cls");
        for (int i = 0;i < 5;++i) {

            for (int j = 0;j < 6;++j) {
                cout << marks[i][j] << "       ";
            }
            cout << endl;
        }

    }

    void coursedisplay() {
        int a = 0;
        cout << "courses taken by the student -> " << studentname << " : " << endl;
        for (int i = 0;i < 5;++i) {
            if (courses[i] != "null") {
                a = 1;
                cout << courses[i] << endl;
            }
        }
        if (a == 0) {
            cout << "NONE." << endl;
        }


    }


};


class course {
    friend class student;
    friend class userinput;
    int code, credits, capacity;
    int students[20];
    string instructor;
    string attendance[30];
    string coursename;
    double marks;

public:
    course() {
        marks = 0;
        code = 0;
        credits = 0;
    }

    course(string a, string b, int c, int d) {
        coursename = a;
        instructor = b;
        code = c;
        credits = d;
        capacity = 20;
        for (int i = 0; i < 20; ++i) {
            students[i] = 0;
        }
    }

    void addstudent(student &a) {
        if (capacity != 0) {
            for (int i = 0; i < 20; ++i) {
                if (students[i] == 0) {
                    students[i] = a.rollno;
                    a.studentedit(coursename, true);
                    --capacity;
                    break;
                }
            }
        }
        else {
            cout << "no more students can be entered in the course" << endl;
        }
    }

    void removestudent(student &a) {
        for (int i = 0; i < 20; ++i) {
            if (students[i] == a.rollno) {
                students[i] = 0;
                a.studentedit(coursename, false);
                for (int j = i + 1; j < 20; ++j) {
                    students[j - 1] = students[j];
                }
                capacity++;
                break;
            }
        }
    }

    void displaycoursestudent() {
        cout << "students roll nos enrolled in course " << coursename << " are :" << endl;
        int a = 20 - capacity;
        for (int i = 0; i < a; ++i) {
            cout << students[i] << endl;
        }
    }
    void displaycourse() {
        cout << " name :" << coursename;
        cout << "          insturctor :" << instructor;
        cout << "          code :" << code;
        cout << "          credits  hours:" << credits;
        cout << "          seats available:" << capacity << endl<<endl<<endl;
    }
};



class userinput {
    int n = 0;                //user input no
    int index = 0;
    student students[100];
    course courses[6];
public:
    void menu() {
        courses[0] = course("oop", "Shazia", 435, 3);
        courses[1] = course("linear", "ali", 535, 3);
        courses[2] = course("CPS", "Rubab", 635, 3);
        courses[3] = course("Eng", "zainab", 735, 3);
        courses[4] = course("OOPLab", "Usman", 835, 1);
        courses[5] = course("Diffrential", "warner", 935, 3);



        while (n != 6) {
            system("cls");
            cout << "1- Enroll a student"<<endl;
        cout << "2- Course Registration"<<endl;
        cout << "3- Attendance"<<endl;
        cout << "4- Marks"<<endl;
        cout << "5- Course Withdraw"<<endl;
        cout << "6- Exit"<<endl;
        cin >> n;
            if (n == 1) {
                n = 0;
                menu1();
            }
            else if (n == 2) {
                n = 0;
                menu2();
            }
            else if (n == 3) {
                menu3();
            }
            else if (n == 4) {
                menu4();
            }
            else if (n == 5) {
                menu5();
            }
            else if (n==6) {
                cout << "exitting" << endl;
                this_thread::sleep_for(chrono::seconds(5));
                system("cls");
            }
            else {
                cout << "invalid input,enter again after 2 sec" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                n = 5;
            }


        }
       }
    void menu1() {
        while (n == 0) {
            system("cls");
            cout << "1. Display enrolled students" << endl;
            cout << "2. Add a student" << endl;
            cout << "3. Remove a student" << endl;
            cout << "4. Edit student details" << endl;
            cout << "5. back" << endl;
            cin >> n;
            system("cls");
            if (n == 1) {
                enrolledstudents(students,index,n );
            }

            else if (n == 2) {
              
                enterstudent(students, index,n);
            }
            else if (n == 3) {
                deletestudents(students,index,n);

            }
            else if (n == 4) {
                studenteditmenu1(students, index, n);
            }
            else if (n == 5) {
                n = 5;
            }
            else {
                cout << "invalid entry enter again" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                n = 0;
            }


        }
        
    }
    void enrolledstudents(student ar[], int& no, int& a) {
        if (no == 0) {
            cout << "No students are enrolled." << endl;
        }
        else {
            cout << "Enrolled students are:" << endl;
              for (int i = 0; i < no; ++i) {
                ar[i].studentdisplay();
                
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        
        a = 0;
    }
    void enterstudent(student ar[], int& no, int& a) {
        string name, uni;  // Fix: Correct variable names
        int rollno;

        system("cls");
        if (no < 100) {
            cout << "Enter student's name, roll no, and university:" << endl;
            cin >> name;
            cin >> rollno;
            cin >> uni;

            ar[no] = student(name, rollno, uni);  // Fix: Use correct variable names and call the constructor
            ++no;

            system("cls");
            cout << "Student has been added successfully. Returning to the main menu..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        else {
            system("cls");
            cout << "No more students can be entered." << endl;
        }
        a = 0;
    }
    void deletestudents(student ar[], int& no, int& a) {
        int x = 0;
        int roll = 0;
        cout << "enter the roll no of the student to delete" << endl;
        cin >> roll;
        system("cls");
        for (int i = 0;i < no;++i) {
            if (ar[i].rollno == roll) {
                for (int j = ++i;j < no;++j) {
                    ar[j - 1] = ar[j];
                }
                --no;
                x = 1;
            }
            else {
                x = 0;
            }
        }
        if (x == 0) {
            cout << "this roll no does not exist in database" << endl;
        }
        else {
            cout << " the  student has been deleted " << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        a = 0;
    }
    void studenteditmenu1(student ar[], int& no, int& a) {
        string d;
        int x = 0;
        int roll = 0;
        cout << " enter the roll no" << endl;
        cin >> roll;
        system("cls");
        for (int i = 0;i < no;++i) {
            if (ar[i].rollno == roll) {
                cout << "1. to change the name" << endl;
                cout << "2. to change the roll no" << endl;
                cout << "3. to change both options 1 and 2" << endl;
                cin >> x;

                    if (x == 1) {
                        cin >> d;
                        ar[i].studentname = d;
                        x = 1;
                    }
                    else if (x == 2) {
                        cin >> x;
                        ar[i].rollno = x;
                        x = 1;
                    }
                    else if (x == 3) {
                        cin >> d;
                        cin >> x;
                        ar[i].studentname = d;
                        ar[i].rollno = x;
                        x = 1;
                    }
                    else {
                        cout << "invalid input" << endl;
                    }
                
            }
            else {
                x = 0;
            }
        }
        if (x == 0) {
            cout << "this roll no does not exist in database" << endl;
        }
        else {
            cout << " the  student details has been edited " << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        a = 0;


     }
    
    //course menu starts from here
    
    void menu2();
    void coursemenu2(course ar[],int &a);
    void registermenu2(student ar[], int no, course arr[], int& a);

    //menu3 
    void menu3();
    void displayattendence(student ar[],course arr[],int no,int &a);
    void markattendence(student ar[],int no,int &a);
    //menu4
    void menu4();
    void displaymarks(student ar[],int no,int &a);
    void assignmarks(student ar[], int no, int& a);
    //menu5
    void menu5();
    void enrolledcourses(student ar[], int no,int &a);
    void dropcourse(student ar[], int no, course arr[], int& a);


};
void userinput::menu2() {
     n = 0;
    while (n == 0) {
        system("cls");
        cout << " 1> Available Courses" << endl;
        cout << " 2> Register course" << endl;
        cout << " 3> back" << endl;
        cin >> n;
        if (n == 1) {
            coursemenu2(courses, n);

        }
        else if (n == 2) {
            registermenu2(students,index,courses,n);
        }
        else if (n == 3) {
            n = 3;
        }
        else {
            cout << "invalid input ,enter again" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            n = 0;
        }






        system("cls");
    }

}
void userinput::coursemenu2(course ar[],int &a) {
    system("cls");
    cout << "available courses are :" << endl << endl;
    for (int i = 0;i < 6;++i) {
        if (ar[i].capacity != 0) {
            ar[i].displaycourse();
        }
    }
    this_thread::sleep_for(chrono::seconds(7));
    a = 0;
}



void userinput::registermenu2(student ar[], int no, course arr[], int& a) {
    system("cls");
    int roll = 0;
    cout << "enter the roll no = ";
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll && ar[i].uni=="fast") {
            system("cls");
            for (int j = 0;j < 6;++j) {
                if (arr[j].capacity != 0) {
                    cout << arr[j].coursename << endl;
                }
                }
            this_thread::sleep_for(chrono::seconds(3));
            cout << endl;
            cout << "enter from 1 to 6 to register the courses available = ";
            cin >> roll;
            if (roll == 1) {
                arr[0].addstudent(ar[i]);
            }
            else if (roll == 2) {
                arr[1].addstudent(ar[i]);
            }
            else if (roll == 3) {
                arr[2].addstudent(ar[i]);
            }
            else if (roll == 4) {
                arr[3].addstudent(ar[i]);
            }
            else if (roll == 5) {
                arr[4].addstudent(ar[i]);
            }
            else if (roll == 6) {
                arr[5].addstudent(ar[i]);
            }
            this_thread::sleep_for(chrono::seconds(5));
            cout << "course has been added" << endl;
        }
    }
    a = 0;

}


void userinput::menu3() {
    n = 0;
    while (n == 0) {
        system("cls");
        cout << "1> Display Attendance(Subject wise)" << endl;
        cout << "2> Mark Attendance." << endl;
        cout << "3> back" << endl;
        cin >> n;
        if (n == 1) {
            displayattendence(students, courses, index,n);
        }
        else if (n == 2) {
            markattendence(students, index, n);
        }
        else if (n == 3) {
            n = 3;
        }
        else {
            cout << "invalid input ,enter again" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            n = 0;
        }



    }
}

void userinput::displayattendence(student ar[], course arr[], int no,int &a) {
    system("cls");
    int roll,x=0,t=0;
    cout << "Enter the roll no of the student to display attendence :" << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll && ar[i].uni=="fast") {
            x = 1;                                  //x set to 1 as student of that roll no exists
            for (int j = 0;j < 5;++j) {
                if (ar[i].courses[j] != "null") {
                    ar[i].attenddisplay();
                    t = 1;
                    break;
                }
                else {
                    t = 0;                                 //t set to 0 if student may have no courses
                }
            
            }

            if (t == 1) {
                break;
            }
            else {
                system("cls");
                cout << "student does not take any courses" << endl;
                break;
            }

        }
    
        else {
            x = 0;
        }

    }
    if (x == 0) {
        system("cls");
        cout << "student of that roll no is not registered in fast uni" << endl;
}
 
    this_thread::sleep_for(chrono::seconds(5));

    a = 0;
}
void userinput::markattendence(student ar[], int no, int& a) {
    a = 0;
    system("cls");
                            //to come out of the loop after marking the attendence
    int roll,noroll=0,t=-1,nn=0;       //t as a check for no course
    string c;                                                                  //c is the course to mark the attencedence
    cout << "enter the roll no of the student to mark attendence :" << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll){ 
            noroll = 1;
                system("cls");
                cout << "enter the course of the student to mark attendence :" << endl;
                cin >> c;
                for (int j = 1;j < 6;++j) {
                    if (ar[i].attend[0][j] == c) {
                        
                        t = 1;
                        while (nn == 0) {
                        system("cls");
                        cout << "enter the day to mark attendence of november mark attendence :" << endl;
                        cin >> roll;                                                                     //day is being entered to mark the attencdence

                        if (roll > 0 && roll < 31) {
                            nn = 1;
                            for (int k = 1;k < 31;++k) {
                                if (k == roll) {
                                    cout << "assign the attendence :" << endl;
                                    cin >> c;
                                    ar[i].attend[k][j] = c;
                                    break;
                                }

                            }
                        }
                        else {
                            cout << "invalid day entered" << endl;
                            cout << " going back" << endl;
                            nn = 0;
                            this_thread::sleep_for(chrono::seconds(5));
                        }


                    }

                        break;
                    }
            
                    else {
                        t = 0;
                    }
                
                }
        
        
        }
        
        else {
            noroll = 0;
        }
    
    
    
    }
    if (t == 0) {
        cout << "student does not exist in that course" << endl;
    }
    if (noroll == 0) {
        cout << "student does not exist in fast" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));
    a = 0;
}

//menu 4
void userinput::menu4() {
    n = 0;
    while (n == 0) {
        system("cls");
        cout << "1> Display Marks(Subject wise)" << endl;
        cout << "2> Assign Marks." << endl;
        cout << "3> back"<< endl;
        cin >> n;
        if (n == 1) {
            displaymarks(students, index, n);
        }
        else if (n == 2) {
            assignmarks(students, index, n);
        }
        else if (n == 3) {
            n = 3;
        }
        else {
            cout << "invalid input ,enter again" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            n = 0;
        }
    
       
    }

}

void userinput::displaymarks(student ar[], int no, int& a) {
    system("cls");
    a = 0;
    int t = 0,x=0;         //checker of courses
    int roll;
    cout << "enter the roll no of the student :" << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll && ar[i].uni=="fast") {
            x = 1;
            for (int j = 0;j < 5;++j) {
                if (ar[i].courses[j] != "null") {
                    t = 1;
                    ar[i].marksdisplay();
                    break;
        
                }
                
                else {
                    t = 0;
                }

            }
                    
            if (t == 1) {
                break;
            }
            else {
                system("cls");
                cout << "student does not take any courses" << endl;
                break;
            }

        }
        else {
            x = 0;
        }

    }
    if (x == 0) {
        system("cls");
        cout << "student of that roll no is not registered in fast uni" << endl;
}

    this_thread::sleep_for(chrono::seconds(5));
    a = 0;

}

void userinput::assignmarks(student ar[], int no, int& a) {

    a = 0;
    system("cls");
   
    int roll, noroll = 0, t = -1, nn = 0;       //t as a check for no course
    string c;                                                                  //c is the course to mark the attencedence
    cout << "enter the roll no of the student to mark attendence :" << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll) {
            noroll = 1;
            system("cls");
            cout << "enter the course of the student to assign marks :" << endl;
            cin >> c;
            for (int j = 1;j < 6;++j) {
                if (ar[i].marks[0][j] == c) {

                    t = 1;
                    while (nn == 0) {
                        system("cls");
                        cout << "enter the exam type of the course :" << endl;
                        cin >> c;                                                                     //day is being entered to mark the attencdence

                        if (c=="assignment" || c == "quiz" || c == "midexam" || c == "finalexam" ) {
                            nn = 1;
                            if (c == "assignment") {                                  //doing just for ease to differentiate between exam type
                                roll = 1;
                            }
                            else if (c == "quiz") {
                                roll = 2;
                            }
                            else if (c == "midexam") {
                                roll = 3;
                            }
                            else if (c == "finalexam") {
                                roll = 4;
                            }


                            for (int k = 1;k < 5;++k) {
                                if (k == roll) {
                                    cout << "assign the marks :" << endl;
                                    cin >> roll;
                                    ar[i].marks[k][j] = to_string(roll);
                                    break;
                                }

                            }
                        }
                        else {
                            cout << "invalid exam type entered" << endl;
                            cout << " going back" << endl;
                            nn = 0;
                            this_thread::sleep_for(chrono::seconds(5));
                        }


                    }

                    break;
                }

                else {
                    t = 0;
                }

            }


        }

        else {
            noroll = 0;
        }



    }
    if (t == 0) {
        cout << "student does not exist in that course" << endl;
    }
    if (noroll == 0) {
        cout << "student does not exist in fast" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));
    a = 0;

}

//menu5 

void userinput::menu5() {
    n = 0;
    system("cls");
    while (n == 0) {
        cout << "1> Enrolled courses" << endl;
        cout << "2> Drop a course" << endl;
        cout << "3> back" << endl;
        cin >> n;
        if (n == 1) {
            enrolledcourses(students, index, n);
        }
        else if (n == 2) {
            dropcourse(students, index, courses, n);
        }
        else if (n == 3) {
            n = 3;
        }
        else {
            cout << "invalid input ,enter again" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            n = 0;
        }





    }

}

void userinput::enrolledcourses(student ar[], int no, int& a) {
    system("cls");
    a = 0;
    int roll,noroll=0;
    cout << "enter the roll no of the student : " << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll && ar[i].uni=="fast") {
            noroll = 1;
            ar[i].coursedisplay();
            break;
        }
        else {
            noroll = 0;
        }
    }

    if (noroll == 0) {
        cout << "the student does not exist in FAST uni" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));
    a = 0;
}

void userinput::dropcourse(student ar[], int no, course arr[], int& a) {
    system("cls");
    a = 0;
    int roll, noroll = 0;
    string c;
    int t = -1;
    cout << "enter the roll no of the student : " << endl;
    cin >> roll;
    for (int i = 0;i < no;++i) {
        if (ar[i].rollno == roll && ar[i].uni=="fast") {
            system("cls");
            noroll = 1;
            for (int j = 0;j < 5;++j) {
                if (ar[i].courses[j] != "null") {
                    t = 1;
                    cout << ar[i].courses[j] << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
           }

            cout <<endl<< "enter the no of the course to drop : " << endl;
            cin >> c;
            for (int j = 0;j < 5;++j) {
                if (arr[j].coursename == c) {
                    arr[j].removestudent(ar[i]);
                    break;
                }
              
            }

            break;
        }


    }

    if (noroll == 0) {
        cout << "student is not registered in Fast uni" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));
    a = 0;

}











int main() {
   /* student a("eliya", 6970);
    student b("hassan", 6625);
    course oop("oop", "fraz", 23, 3);
    oop.addstudent(a);
    oop.addstudent(b);
    oop.displaycoursestudent();
    b.studentdisplay();*/
    userinput a;
    a.menu();
   
    return 0;
}
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
vector<string> semesterinput;
vector<string> subjectinput;
vector<string> professor_nameinput;
vector<string> creditinput;
vector<string> branchinput;
const int Total_Rooms = 23; 
const int Total_slots = 5;
vector<vector<vector<string>>> Course_Allocation(Total_Rooms, vector<vector<string>>(Total_slots, vector<string>(5, "0")));
bool Is_Prof_Avail(int timing, int day, string Prof, int room);
void Generate_Timetable();
void PrintTimeTable();

int main() {
    string semester;
    cout << "Enter semester (winter/autmn): ";
    cin >> semester;
    
    string filename = (semester == "winter") ? "winter.txt" : "autmn.txt";
    ifstream input(filename);
    
    if (!input) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    string perticularline;
    while (getline(input, perticularline)) {
        istringstream iss(perticularline);
        string sem, sub, pro_n, cre, br;
        if (getline(iss, sem, ',') && getline(iss, sub, ',') && getline(iss, pro_n, ',') && getline(iss, cre, ',') && getline(iss, br, ' ')) {
            semesterinput.push_back(sem);
            subjectinput.push_back(sub);
            professor_nameinput.push_back(pro_n);
            creditinput.push_back(cre);
            branchinput.push_back(br);
        }
    }

    Generate_Timetable();
    PrintTimeTable();

    return 0;
}

bool Is_Prof_Avail(int timing, int day, string Prof, int room) {
    vector<string> code;
    for (int i = 0; i < professor_nameinput.size(); ++i) {
        if (Prof == professor_nameinput[i]) {
            code.push_back(subjectinput[i]);
        }
    }
    for (int j = 0; j < code.size(); ++j) {
        for (int i = 0; i < room; ++i) {
            if (Course_Allocation[i][timing][day] == code[j]) {
                return false;
            }
        }
    }
    return true;
}

void Generate_Timetable() {
    int course_index = 0;
    for (int i = 0; i < Total_Rooms; i++) {
        for (int j = 0; j < Total_slots; j++) {
            for (int k = 0; k < 5; k++) {
                if (course_index < subjectinput.size() && Is_Prof_Avail(j, k, professor_nameinput[course_index], i) && stoi(creditinput[course_index]) > 0) {
                    Course_Allocation[i][j][k] = subjectinput[course_index];
                    creditinput[course_index] = to_string(stoi(creditinput[course_index]) - 1); 
                    if(stoi(creditinput[course_index])==0)
                    course_index++; 
                }
            }
        }
    }
}

 void PrintTimeTable() {
    for(int k = 0; k < 5; ++k) {
        if(k==0)
            cout << "Monday TimeTable:" << endl;
        if(k==1)
            cout << "Tuesday TimeTable:" << endl;
        if(k==2)
            cout << "Wednesday TimeTable:" << endl;
        if(k==3)
            cout << "Thursday TimeTable:" << endl;
        if(k==4)
            cout << "Friday TimeTable:" << endl;

        for(int j = 0; j < 5; ++j) {
            if(j==0)
                cout << "Time: 8:00 AM - 9:00 AM" << endl;
            if(j==1)
                cout << "Time: 9:00 AM - 10:00 AM" << endl;
            if(j==2)
                cout << "Time: 10:00 AM - 11:00 AM" << endl;
            if(j==3)
                cout << "Time: 11:00 AM - 12:00 PM" << endl;
            if(j==4)
                cout << "Time: 12:00 PM - 1:00 PM" << endl;

            for(int i = 0; i < 23; ++i) {
                if (Course_Allocation[i][j][k] != "0") { 
                    cout << "Course: " << Course_Allocation[i][j][k] << "  ";
                    int courseIndex = -1;
                    for (int idx = 0; idx < subjectinput.size(); ++idx) {
                        if (Course_Allocation[i][j][k] == subjectinput[idx]) {
                            courseIndex = idx;
                            break;
                        }
                    }
                    if (courseIndex != -1) {
                        cout << "Professor: " << professor_nameinput[courseIndex] << "  ";
                        cout << "Semester: " << semesterinput[courseIndex] << "  ";
                        cout << "Branch: " << branchinput[courseIndex] << "  ";
                        cout << "Room: ";
                        if (i == 0) cout << "LT1";
                         if (i == 1) cout << "LT2";
                        if (i == 2) cout << "LT3";
                        if(i==3)
                    cout<<"CEP-003";
                    if(i==4)
                    cout<<"CEP-102";
                    if(i==5)
                    cout<<"CEP-103";
                    if(i==6)
                    cout<<"CEP-104";
                    if(i==7)
                    cout<<"CEP-105";
                    if(i==8)
                    cout<<"CEP-106";
                    if(i==9)
                    cout<<"CEP-107";
                    if(i==10)
                    cout<<"CEP-108";
                    if(i==11)
                    cout<<"CEP-109";
                    if(i==12)
                    cout<<"CEP-110";
                    if(i==13)
                    cout<<"CEP-202";
                    if(i==14)
                    cout<<"CEP-203";
                    if(i==15)
                    cout<<"CEP-204";
                    if(i==16)
                    cout<<"CEP-205";
                    if(i==17)
                    cout<<"CEP-206";
                    if(i==18)
                    cout<<"CEP-207";
                    if(i==19)
                    cout<<"CEP-209";
                    if(i==20)
                    cout<<"CEP-210";
                    if(i==21)
                    cout<<"CEP-211";
                    if(i==22)
                    cout<<"CEP-212";
                    }
                    cout << endl;
                }
            }
            cout << endl;
        }
        cout << endl << endl << endl;
    }  
}
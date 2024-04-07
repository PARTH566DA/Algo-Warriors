#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;


vector<string> semesterinput;                    //This is a vector to store semester number for each course
vector<string> subjectinput;                     //This is a vector to store course code for each course
vector<string> professor_nameinput;              //This is a vector to store professor code for each course
vector<string> creditinput;                      //This is a vector to store frequency in a week of each course
vector<string> branchinput;                      //This is a vector to store branch name for each course
unordered_map<string,string> shortToFullName;    //This is an unordered map to map professor code with his full name
unordered_map<string,string> branch;             //This is an unordered map to map branch short name to full detailed branch name
vector<string> semesterinput_elective;           //This is a vector to store semester number for each elective course(If there is 68 ,it means it is in both the semesters)
vector<string> subjectinput_elective;            //This is a vector to store course code for each elective course
vector<string> professor_nameinput_elective;    //This is a vector to store professor code for each elective course
vector<string> creditinput_elective;            //This is a vector to store frequency in a week of each elective course
vector<string> branchinput_elective;            //This is a vector to store branch name for each elective course


const int Total_Rooms = 23;         //This is the total room available for allocation
const int Total_slots = 5;          //This is the total slots available on each day for allocation
const int Total_slots_elective = 2;     //This is the total room available for elective courses allocation


vector<vector<vector<string> > > Course_Allocation(Total_Rooms, vector<vector<string> >(Total_slots, vector<string>(5, "0")));  //Main vector to store allocated course
vector<vector<vector<string> > > Course_Allocation_elective(Total_Rooms, vector<vector<string> >(Total_slots_elective, vector<string>(5, "0")));//Main vector to store allocated elective course

bool string_match_elective(int branch_index,int k) ;
bool Is_Prof_Avail(int var,int timing, int day, string Prof, int room);   //Check professor availibility
void Generate_Timetable(int k,vector<vector<vector<string> > > &Course_Allocation_temp,vector<string> &subjectinput_temp,vector<string> &professor_nameinput_temp,vector<string> &creditinput_temp,int Total_slots_temp);
        //Allocate the courses
void WriteTimetableToFile(const string& filename);        //Print Timetable in csv file
void Professor_TimeTable(const string& professorName);    //Print TimeTable with respect to professor in csv file
void Semester_TimeTable(const string& Semester);          //Print TimeTable for a particular semester in csv file
void WriteTimetableToFile_elective(const string& filename);    //Print elective TimeTable in csv file 


int main() {

    // Mapping of branch codes to their full names.
    branch["ICT"] = "B.Tech ICT";
    branch["CS"] = "B.Tech ICT+CS";
    branch["CSEVD"] = "B.Tech ICT+CS; EVD";
    branch["CSEVDCSMNC"] = "B.Tech ICT+CS; MNC; EVD";
    branch["EVD"] = "B.Tech EVD";
    branch["MNC"] = "B.Tech MnC";
    branch["CSMNC"] = "B.Tech ICT+CS; MnC";
    branch["MICT"] = "M.Tech ICT";
    branch["MEC"] = "M.Tech EC";
    branch["MSCIT"] = "M.Sc IT";
    branch["MSCDS"] = "M.Sc DS";
    branch["MSCAA"] = "M.Sc AA";
    branch["MDES"] = "M.Des CD";
    branch["ICTCS"] = "B.Tech ICT Elective";
    branch["ICTCSMNC"] = "B.Tech ICT; MnC Elective";

    // Mapping of short form of professor names to their full names.
    shortToFullName["AJ"] = "Abhishek Jindal";
    shortToFullName["AKM"] = "Amit Mankodi";
    shortToFullName["AG"] = "Anjan Ghosh";
    shortToFullName["AR"] = "Arnab Ray";
    shortToFullName["AT"] = "Aditya Tatu";
    shortToFullName["AKR"] = "Anil K Roy";
    shortToFullName["AT2"] = "Anuj Tawari";
    shortToFullName["AMM"] = "Anish Mathuria";
    shortToFullName["AR2"] = "Arpit Rana";
    shortToFullName["BD"] = "Binita Desai";
    shortToFullName["BK"] = "Bharani Kollipara";
    shortToFullName["BC"] = "Bhaskar Chaudhury";
    shortToFullName["BG"] = "Bakul Gohel";
    shortToFullName["BM"] = "Biswajit Mishra";
    shortToFullName["DKG"] = "Deepak K Ghodgaonkar";
    shortToFullName["GD"] = "Gautam Dutta";
    shortToFullName["GP"] = "Gopinath Panda";
    shortToFullName["GV"] = "Gaurav Vaidya";
    shortToFullName["HP"] = "Hemn Patil";
    shortToFullName["JP"] = "JayPrakash";
    shortToFullName["JM"] = "Jaydeep Mulherkar";
    shortToFullName["JJ"] = "Jensen Joseph";
    shortToFullName["PKS"] = "Kalyan Sasidhar";
    shortToFullName["LS"] = "Lavneet Singh";
    shortToFullName["MB"] = "Minal Bhise";
    shortToFullName["MK"] = "Manish Khare";
    shortToFullName["MK2"] = "Manish Kumar";
    shortToFullName["MM"] = "Madhumita Mazumdar";
    shortToFullName["MS"] = "Madhukant Sharma";
    shortToFullName["MT"] = "Mukesh Tiwari";
    shortToFullName["MKG"] = "Manish K Gupta";
    shortToFullName["MKR"] = "Manoj K Raut";
    shortToFullName["MLD"] = "Manik Lal Das";
    shortToFullName["MVJ"] = "Manjunath V Joshi";
    shortToFullName["NKS"] = "Nabin K Sahu";
    shortToFullName["PM"] = "Prasenjit Majumder";
    shortToFullName["PMJ"] = "Pokhar M Jat";
    shortToFullName["PA"] = "Pritam Anand";
    shortToFullName["PB"] = "Puneet Bhateja";
    shortToFullName["PK"] = "Pankaj Kumar";
    shortToFullName["PK2"] = "Prosenjit Kundu";
    shortToFullName["RG"] = "Ranendu Ghosh";
    shortToFullName["RLD"] = "Rajib L Das";
    shortToFullName["RM"] = "Rahul Muthu";
    shortToFullName["RC"] = "Rachit Chhaya";
    shortToFullName["RM2"] = "Rahul Mishra";
    shortToFullName["RP"] = "Rutu Parekh";
    shortToFullName["SDG"] = "Sourish Dasgupta";
    shortToFullName["SR"] = "Sreeja Rajendran";
    shortToFullName["SS"] = "S Srivastava";
    shortToFullName["SJ"] = "Shefali Jha";
    shortToFullName["SRG"] = "Shweta R Garg";
    shortToFullName["SB"] = "Shruti Bhilare";
    shortToFullName["SM"] = "Srimanta Mandal";
    shortToFullName["SB2"] = "Sudip Bera";
    shortToFullName["SK"] = "Sujay Kadam";
    shortToFullName["SP"] = "Supantha Pandit";
    shortToFullName["ST"] = "Saurabh Tiwari";
    shortToFullName["TKM"] = "Tapas K Maity";
    shortToFullName["VP"] = "Vishvajit Pandya";
    shortToFullName["VS"] = "V Sunitha";
    shortToFullName["VSP"] = "Vinay S Palaparthy";
    shortToFullName["YA"] = "Yash Agrawal";
    shortToFullName["YV"] = "Yash Vasavada";
    shortToFullName["NDJ"] = "Naresh D Jotwani";
    shortToFullName["TB"] = "gata Bandyopadhyay";
    shortToFullName["DNC"] = "Dipankar Nag Chaudhury";
    shortToFullName["GKS"] = "Gaurav Kumar Singh";
    shortToFullName["CJ"] = "Cyril Jos";
    shortToFullName["AM"] = "Amishal Modi";
    shortToFullName["NIKITADESAI"] = "Nikita Desai";
    shortToFullName["ANIRBANDUTTAGUPTA"] = "Anirban Duttagupta";
    shortToFullName["KUNTALADASGUPTA"] =  "Kuntala Dasgupta";
    shortToFullName["SANDIP MODHA"] = "Sandip Modha";
    shortToFullName["NANDINISAHA"] = "Nandini Saha";
    shortToFullName["MAYANKLOONKAR"] = "Mayank Loonkar";
    shortToFullName["PROSENJITGANGULY"] = "Prosenjit Ganguly";
    shortToFullName["RUDRANILDAS"] = "Rudranil Das";


    //Read data from a file based on the semester input and store it in corresponding vectors.
    string semester;
    label:

    cout << "Enter semester (winter/autumn): ";
    cin >> semester;

    // Check if the file can be opened. If not, display an error message and exit.
    string filename;
    if(semester == "winter"){
        filename = "winter.txt";
    }
    else if(semester == "autumn"){
        filename = "autumn.txt";
    }
    else{
        cout << endl << "Please Enter valid Input. Try again." << endl << endl;
        goto label;
    }

    ifstream input(filename);
    
    if (!input) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    // Read each line from the file and extract relevant information.
    string perticularline;
    while (getline(input, perticularline)) {
    // Parse each line to extract semester, subject, professor name, credit, and branch.
        istringstream iss(perticularline);
        string sem, sub, pro_n, cre, br;
        if (getline(iss, sem, ',') && getline(iss, sub, ',') && getline(iss, pro_n, ',') && getline(iss, cre, ',') && getline(iss, br, ',')) {
            // Store the extracted information into corresponding vectors.
            semesterinput.push_back(sem);
            subjectinput.push_back(sub);
            professor_nameinput.push_back(pro_n);
            creditinput.push_back(cre);
            branchinput.push_back(br);
        }
    }

    Generate_Timetable(0,Course_Allocation,subjectinput,professor_nameinput,creditinput,Total_slots);
    cout << endl << "Timetable has been saved." << endl << endl;

    cout << "Do you want time table with respect to Professor? (YES/NO)" << endl;     //Asked the user if he want timetable with respect to professor or not? 
    string yesno;
    cin >> yesno;
    cout << endl;
    
    if(yesno=="YES"){
        string proff_name;
        cout << "Enter the Professor code for whome you need Timetable." << endl;       //Asked for professor code for generating time table
        cin >> proff_name;
        Professor_TimeTable(proff_name);
        cout << endl;
        cout << "Time table for " << proff_name << " has been saved successfully" << endl;
    }
    cout << endl << "Do you want Time Table according to semester? (YES/NO)" << endl;        //Asked the user if he want timetable for a particular semester or not?
    string yn;
    cin >> yn;
    string Semester;
    if(yn=="YES"){
        cout << endl << "Enter Semester Number." << endl;           
        cin >> Semester;
        Semester_TimeTable(Semester);
        cout << endl;
        cout << "Time table for " << Semester << " semester has been saved successfully" << endl;
    }

    WriteTimetableToFile("timetable.csv");
    cout << endl << "Time Table has been Saved" << endl << endl << endl;
    cout << "Do you want Time Table for Elective courses? (YES/NO)" << endl;
    string temp;
    cin >> temp;        //Asked for generating time table for Elective course.
    if(temp == "YES"){
        //Read data from a file based on the semester input(for Elective course) and store it in corresponding vectors.
        string semester_elective;
        label1:
        cout << endl << "Enter semester for Elective (winter/autumn): ";
        cin >> semester_elective;
        
        // Check if the Elective_file can be opened. If not, display an error message and exit.
        string filename_elective;
        if(semester_elective == "winter"){
            filename_elective = "winter_elective.txt";
        }
        else if(semester_elective == "autumn"){
            filename_elective = "autumn_elective.txt";
        }
        else{
            cout << endl << "Please Enter valid Input. Try again." << endl << endl;
            goto label1;
        }

        ifstream input_elective(filename_elective);
    
        if (!input_elective) {
            cerr << "Error: Unable to open file " << filename_elective << endl;
            return 1;
        }
        // Read each line from the Elective_file and extract relevant information.
        string perticularline_elective;
        while (getline(input_elective, perticularline_elective)) {
        // Parse each line to extract semester, subject, professor name, credit, and branch for Elective course.
            istringstream iss(perticularline_elective);
            string sem_elective, sub_elective, pro_n_elective, cre_elective, br_elective;
            if (getline(iss, sem_elective, ',') && getline(iss, sub_elective, ',') && getline(iss, pro_n_elective, ',') && getline(iss, cre_elective, ',') && getline(iss, br_elective, ',')) {
                // Store the extracted information into corresponding vectors.
                semesterinput_elective.push_back(sem_elective);
                subjectinput_elective.push_back(sub_elective);
                professor_nameinput_elective.push_back(pro_n_elective);
                creditinput_elective.push_back(cre_elective);
                branchinput_elective.push_back(br_elective);
            }
        }



        Generate_Timetable(1,Course_Allocation_elective,subjectinput_elective,professor_nameinput_elective,creditinput_elective,Total_slots_elective);
        WriteTimetableToFile_elective("timetable_elective.csv");

        cout << endl << "Time table for elective has been saved." << endl;

    }
    return 0;
}

// the below function is Check if two branch codes match or have a similar prefix for Elective course.
bool string_match_elective(int branch_index,int k) 
{ 
    vector<string>branch_index2; 
    vector<string>curr_branch; 
    curr_branch.push_back(branchinput_elective[k]); 
    branch_index2.push_back(branchinput_elective[branch_index]); 
    if(curr_branch[0][0]=='M'&&branch_index2[0][0]!='M') 
    { 
        return false; 
    } 
    if(curr_branch[0][0]!='M'&&branch_index2[0][0]=='M') 
    { 
        return false; 
    } 
    // Check if branch codes match or have a similar prefix.
    bool found = (curr_branch[0].find(branch_index2[0]) != string::npos); 
 
    if (found) { 
        return true; 
    } else { 
        // If branch codes do not match, check if they have a similar prefix
        bool found = (branch_index2[0].find(curr_branch[0]) != string::npos); 
        if(found){ 
            return true; 
        } 
        else{ 
            return false; 
        } 
    } 
}

// the below function is Check if two branch codes match or have a similar prefix.
bool string_match(int branch_index,int k)
{
    vector<string>branch_index2;
    vector<string>curr_branch;
    curr_branch.push_back(branchinput[k]);
    branch_index2.push_back(branchinput[branch_index]);
    if(curr_branch[0][0]=='M'&&branch_index2[0][0]!='M')
    {
        return false;
    }
    if(curr_branch[0][0]!='M'&&branch_index2[0][0]=='M')
    {
        return false;
    }
    // Check if branch codes match or have a similar prefix
    bool found = (curr_branch[0].find(branch_index2[0]) != string::npos);

    if (found) {
        return true;
    } else {
        // If branch codes do not match, check if they have a similar prefix
        bool found = (branch_index2[0].find(curr_branch[0]) != string::npos);
        if(found){
            return true;
        }
        else{
            return false;
        }
    }
}

bool Is_Prof_Avail(int var,int timing, int day, string Prof, int room,int branch_index) { 
    if(var==0){
    vector<string> code; 
    //code is the vector that contains all course of the Professor which is passed as argument 
    for (int i = 0; i < professor_nameinput.size(); ++i) { 
        if (Prof == professor_nameinput[i]) { 
            code.push_back(subjectinput[i]); 
        } 
    } 
     //the loop below  checks if any course of given Professor is already alocated in this slot or not 
    if(timing<4) 
        { 
         if(timing>0) 
         { 
              // Check neighboring slots if timing is not at the start or end of the day
              for(int t=timing-1;t<=timing+1;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
         } 
         else 
         { 
             // Check neighboring slots if timing is at the start of the day
             for(int t=timing;t<=timing+1;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
         } 
        } 
        else 
        { 
            // Check neighboring slots if timing is at the end of the day
            for(int t=timing-1;t<=timing;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
        } 
    // Check if there is a course scheduled for the same branch and semester
    for(int i=0;i<room;++i)
   {
    for(int k=0;k<subjectinput.size();++k)
    {
        if(Course_Allocation[i][timing][day]==subjectinput[k])
        {
            if(((branchinput[k]==branchinput[branch_index])||(string_match(branch_index,k)))&&(semesterinput[k]==semesterinput[branch_index]))
            {
                return false;
            }
        }
    }
  }
    return true; 
}
else
{
  //Check if the professor is available for an Elective course at the given timing, day, and room.
  vector<string>code_elective;
  for (int i = 0; i < professor_nameinput_elective.size(); ++i) {
        if (Prof == professor_nameinput_elective[i]) {
            code_elective.push_back(subjectinput_elective[i]);
        }
    }
    
if(timing<1)
{
        for(int t=timing;t<=timing+1;++t){
         for (int j = 0; j < code_elective.size(); ++j) {
                for (int i = 3; i <= room; ++i) {
                    if (Course_Allocation_elective[i][t][day] == code_elective[j]) {
                        return false;
                    }
                }
            }
         }
     
}
 return true;
  
}

}

void Generate_Timetable(int z,vector<vector<vector<string> > > &Course_Allocation_temp,vector<string> &subjectinput_temp,vector<string> &professor_nameinput_temp,vector<string> &creditinput_temp,int Total_slots_temp){
    int course_index = 0;
    while(course_index < subjectinput_temp.size())     // Loop until all courses are scheduled
        {
           for (int i = 0; i < Total_Rooms; i++) {     // Loop through all available rooms
               for (int j = 0; j < Total_slots_temp; j++) {   // Loop through all time slots
                   for (int k = 0; k < 5; k++) {        // Loop through all days of the week

                       // Check if the slot is available, the professor is available, and if there are remaining credits for the course
                       if (Course_Allocation_temp[i][j][k]=="0" && course_index < subjectinput_temp.size() && Is_Prof_Avail(z,j, k, professor_nameinput_temp[course_index], i,course_index) && stoi(creditinput_temp[course_index]) > 0) {
                           Course_Allocation_temp[i][j][k] = subjectinput_temp[course_index];   // Assign the course to the slot
                           creditinput_temp[course_index] = to_string(stoi(creditinput_temp[course_index]) - 1);   // Decrease credit by one from the course
                           if(stoi(creditinput_temp[course_index])==0)
                           course_index++;      // Move to the next course if all credits are scheduled
                      }
                   }
               }
           }
       }
  }





void Professor_TimeTable(const string& professorName) {
    

    string filename = shortToFullName[professorName] + "_timetable.csv";
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    vector<string> days;        // Define vectors for days of the week.
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;       // Define vectors for time slots.
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    outfile << "Day,Timing,Course,Semester,Branch" << endl;


    // Write headers
    for(int k = 0; k < 5; k++) {
        string day = days[k];
        bool dayPrinted = false;

        for(int j = 0; j < Total_slots; j++) {
            string time = times[j];
            bool timeprinted = false;

            for (int i = 0; i < Total_Rooms; i++) {
                for(int f = 0; f < professor_nameinput.size(); f++) {
                    if(professor_nameinput[f] == professorName && subjectinput[f] == Course_Allocation[i][j][k]) {
                        if (!dayPrinted) {
                            outfile << day << ",";
                            dayPrinted = true;
                        } else {
                            outfile << ",";
                        }

                        // Print time if it's not already printed.
                        if (!timeprinted) {
                            outfile << time << ",";
                            timeprinted = true;
                        } else {
                            outfile << ",";
                        }

                        outfile << subjectinput[f] << ",";
                        outfile << semesterinput[f] << ",";
                        outfile << branch[branchinput[f]] << ",";

                        // Assuming i corresponds to room index, print room name based on index
                        if (i == 0) outfile << "LT1";
                        else if (i == 1) outfile << "LT2";
                        // add more else-if conditions for other rooms
                        outfile << endl;
                    }
                }
            }
        }
    }

    outfile.close();
}


void WriteTimetableToFile(const string& filename) {
    ofstream outfile(filename);  // Open the output file stream for writing the timetable.
    if (!outfile) {              // Check if the file stream is successfully opened.
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Write headers for the timetable csv file.
    outfile << "Day,Time,Room,Course,Professor,Semester,Branch" << endl;

    vector<string> days;        // Define vectors for days of the week.
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;       // Define vectors for time slots.
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    // Arrays to keep track of whether each day and time slot has been printed.
    bool printedDays[5] = {false};
    bool printedTimes[5] = {false};


    for (int k = 0; k < 5; ++k) {      // Loop through each day of the week.
        string day = days[k];

        // Check if the day has been printed already
        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < 5; ++j) {      // Loop through each time slot.
                string time=times[j];
                bool timeprinted = false;

                bool slotPrinted = false;
                for (int i = 0; i < 23; ++i) {        // Loop through each room.
                    if (Course_Allocation[i][j][k] != "0") {        // Check if a course is allocated in the current room, time slot, and day.

                        // Print day if it's not already printed.
                        if (!dayPrinted) {
                            outfile << day << ",";
                            dayPrinted = true;
                            printedDays[k] = true;
                        } else {
                            outfile << ",";
                        }

                        // Print time if it's not already printed.
                        if(!timeprinted) {
                            outfile << time << ",";
                            timeprinted = true;
                            printedTimes[k] = true;
                        }
                        else{
                            outfile<< ",";
                        }

                        // Print room based on its index.
                        if (i == 0) outfile << "LT1";
                        else if (i == 1) outfile << "LT2";
                        else if (i == 2) outfile << "LT3";
                        else if (i == 3) outfile << "CEP-003";
                        else if (i == 4) outfile << "CEP-102";
                            else if (i == 5) outfile << "CEP-103";
                            else if (i == 6) outfile << "CEP-104";
                            else if (i == 7) outfile << "CEP-105";
                            else if (i == 8) outfile << "CEP-106";
                            else if (i == 9) outfile << "CEP-107";
                            else if (i == 10) outfile << "CEP-108";
                            else if (i == 11) outfile << "CEP-109";
                            else if (i == 12) outfile << "CEP-110";
                            else if (i == 13) outfile << "CEP-202";
                            else if (i == 14) outfile << "CEP-203";
                            else if (i == 15) outfile << "CEP-204";
                            else if (i == 16) outfile << "CEP-205";
                            else if (i == 17) outfile << "CEP-206";
                            else if (i == 18) outfile << "CEP-207";
                            else if (i == 19) outfile << "CEP-209";
                            else if (i == 20) outfile << "CEP-210";
                            else if (i == 21) outfile << "CEP-211";
                            else if (i == 22) outfile << "CEP-212";
                        outfile << "," << Course_Allocation[i][j][k] << ",";

                         // Find the index of the course in the input vectors.
                        int courseIndex = -1;
                        for (int idx = 0; idx < subjectinput.size(); ++idx) {
                            if (Course_Allocation[i][j][k] == subjectinput[idx]) {
                                courseIndex = idx;
                                break;
                            }
                        }
                         // If course found, write professor, semester, and branch.
                        if (courseIndex != -1) {
                            outfile << professor_nameinput[courseIndex] << ",";
                            outfile << semesterinput[courseIndex] << ",";
                            outfile << branch[branchinput[courseIndex]];
                        }
                        outfile << endl;
                        slotPrinted = true;   // Mark that a course is printed in this slot
                    }
                }
                if (!slotPrinted && dayPrinted) {
                    outfile << "," << time << endl;
                }
            }
        }
    }
    // Close the output file stream.
    outfile.close();
}



void Semester_TimeTable(const string& Semester) {
    // Construct the filename for the timetable CSV file based on the semester.
    string filename = Semester + "_timetable.csv";
    // Open the output file stream for writing the timetable.
    ofstream outfile(filename);
    if (!outfile) {   // Check if the file stream is successfully opened.
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    
    // Write headers for the timetable CSV file.
    outfile << "Day,Time,Course,Professor,Branch,Room" << endl;

    // Define vectors for days of the week and time slots.
    vector<string> days;
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    // Arrays to keep track of whether each day and time slot has been printed.
    bool printedDays[5] = {false};
    bool printedTimes[5] = {false};

    for (int k = 0; k < 5; k++) {   // Loop through each day of the week.
        string day = days[k];

        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < Total_slots; j++) {
                string time = times[j];
                bool timeprinted = false;
                bool slotPrinted = false;
                for (int i = 0; i < Total_Rooms; i++) {   // Loop through each room and professor input.
                    for (int f = 0; f < professor_nameinput.size(); f++) { 
                        // Check if the course matches the semester and day.
                        if (semesterinput[f] == Semester && subjectinput[f] == Course_Allocation[i][j][k]) { 
                            // Print day if it's not already printed.
                            if (!dayPrinted) {
                                outfile << day << ",";
                                dayPrinted = true;
                                printedDays[k] = true;
                            } else {
                                outfile << ",";
                            }

                            // Print time if it's not already printed.
                            if (!timeprinted) {
                                outfile << time << ",";
                                timeprinted = true;
                                printedTimes[k] = true;
                            } else {
                                outfile << ",";
                            }

                            // Write course details: name, professor, branch, and room.
                            outfile << subjectinput[f] << ",";
                            outfile << professor_nameinput[f] << ",";
                            outfile << branch[branchinput[f]] << ",";

                            // Write room based on its index.
                            if (i == 0) outfile << "LT1" << ",";
                            else if (i == 1) outfile << "LT2" << ",";
                            else if (i == 2) outfile << "LT3" << ",";
                            else if (i == 3) outfile << "CEP-003" << ",";
                            else if (i == 4) outfile << "CEP-102" << ",";
                            else if (i == 5) outfile << "CEP-103" << ",";
                            else if (i == 6) outfile << "CEP-104" << ",";
                            else if (i == 7) outfile << "CEP-105" << ",";
                            else if (i == 8) outfile << "CEP-106" << ",";
                            else if (i == 9) outfile << "CEP-107" << ",";
                            else if (i == 10) outfile << "CEP-108" << ",";
                            else if (i == 11) outfile << "CEP-109" << ",";
                            else if (i == 12) outfile << "CEP-110" << ",";
                            else if (i == 13) outfile << "CEP-202" << ",";
                            else if (i == 14) outfile << "CEP-203" << ",";
                            else if (i == 15) outfile << "CEP-204" << ",";
                            else if (i == 16) outfile << "CEP-205" << ",";
                            else if (i == 17) outfile << "CEP-206" << ",";
                            else if (i == 18) outfile << "CEP-207" << ",";
                            else if (i == 19) outfile << "CEP-209" << ",";
                            else if (i == 20) outfile << "CEP-210" << ",";
                            else if (i == 21) outfile << "CEP-211" << ",";
                            else if (i == 22) outfile << "CEP-212" << ",";

                            outfile << endl;
                        }
                    }
                }
            }
        }
    }

    outfile.close();   // Close the output file stream.
}
void WriteTimetableToFile_elective(const string& filename) {
    ofstream outfile(filename);     // Open the output file stream for writing the timetable.
    if (!outfile) {         // Check if the file stream is successfully opened.
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Write headers
    outfile << "Day,Time,Room,Course,Professor,Semester,Branch" << endl;

    vector<string> days;    // Define vectors for days of the week.
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;   // Define vectors for time slots.
    times.push_back("4:00 PM - 5:00 PM");
    times.push_back("5:00 AM - 6:00 AM");
    // Arrays to keep track of whether each day and time slot has been printed.
    bool printedDays[5] = {false};
    bool printedTimes[2] = {false};


    for (int k = 0; k < 5; ++k) {   // Loop through each day of the week.
        string day = days[k];

        // Check if the day has been printed already
        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < 2; ++j) {   // Loop through each time slot.
                string time=times[j];
                bool timeprinted = false;

                bool slotPrinted = false;
                    for (int i = 0; i < 23; ++i) {  // Loop through each room.
                    if (Course_Allocation_elective[i][j][k] != "0") {    // Check if a course is allocated in the current room, time slot, and day.
                        // Print day if it's not already printed.
                        if (!dayPrinted) {
                            outfile << day << ",";
                            dayPrinted = true;
                            printedDays[k] = true;
                        } else {
                            outfile << ",";
                        }
                        // Print time if it's not already printed.
                        if(!timeprinted) {
                            outfile << time << ",";
                            timeprinted = true;
                            printedTimes[k] = true;
                        }
                        else{
                            outfile<< ",";
                        }

                        // Print room based on its index.
                        if (i == 0) outfile << "CEP-003";
                        else if (i == 1) outfile << "CEP-102";
                            else if (i == 2) outfile << "CEP-103";
                            else if (i == 3) outfile << "CEP-104";
                            else if (i == 4) outfile << "CEP-105";
                            else if (i == 5) outfile << "CEP-106";
                            else if (i == 6) outfile << "CEP-107";
                            else if (i == 7) outfile << "CEP-108";
                            else if (i == 8) outfile << "CEP-109";
                            else if (i == 9) outfile << "CEP-110";
                            else if (i == 10) outfile << "CEP-202";
                            else if (i == 11) outfile << "CEP-203";
                            else if (i == 12) outfile << "CEP-204";
                            else if (i == 13) outfile << "CEP-205";
                            else if (i == 14) outfile << "CEP-206";
                            else if (i == 15) outfile << "CEP-207";
                            else if (i == 16) outfile << "CEP-209";
                            else if (i == 17) outfile << "CEP-210";
                            else if (i == 18) outfile << "CEP-211";
                            else if (i == 19) outfile << "CEP-212";
                            else if (i == 20) outfile << "LT1";
                            else if (i == 21) outfile << "LT2";
                            else if (i == 22) outfile << "LT3"; 
                        outfile << "," << Course_Allocation_elective[i][j][k] << ",";
                        // Find the index of the elective course in the input vectors.
                        int courseIndex = -1;
                        for (int idx = 0; idx < subjectinput_elective.size(); ++idx) {
                            if (Course_Allocation_elective[i][j][k] == subjectinput_elective[idx]) {
                                courseIndex = idx;
                                break;
                            }
                        }
                        // If course found and it is only for one semester, write professor, semester, and branch.
                        if(semesterinput_elective[courseIndex].size()==1){
                            
                            outfile << professor_nameinput_elective[courseIndex] << ",";
                            outfile << semesterinput_elective[courseIndex] << ",";
                            outfile << branch[branchinput_elective[courseIndex]];
                            outfile << endl;
                        }
                        // If course found and it is only for more than one semester, write professor, semester, and branch for each the semester.
                        else{
                        for(int t=0;t<semesterinput_elective[courseIndex].size();t++){
                        if ((courseIndex != -1) && (semesterinput_elective[courseIndex][t]>=48) &&(semesterinput_elective[courseIndex][t]<=57)) {
                            outfile << professor_nameinput_elective[courseIndex] << ",";
                            outfile << semesterinput_elective[courseIndex][t] << ",";
                            outfile << branch[branchinput_elective[courseIndex]];
                            if(t!=semesterinput_elective[courseIndex].size()-1){
                            outfile << endl;
                            outfile << "," << "," << "," << ",";
                            }
                            else{
                                outfile << endl;
                           
                            }
                            
                        }
                        }
           }
                        
                        slotPrinted = true;         // Mark that a course is printed in this slot
                    }
                }
                if (!slotPrinted && dayPrinted) {
                    outfile << "," << time << endl;
                }
            }
        }
    }
    // Close the output file stream.
    outfile.close();
}

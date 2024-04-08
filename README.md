# Automatic Timetable Generator

 This C++ code implements a program for generating and managing academic timetables based on input data including course details, professor information, and semester schedules. The program organizes courses into time slots across different days of the week and rooms, ensuring professors' availability, credit allocation for courses, and adherence to branch and semester constraints. It uses file input/output operations to read course information from external files and writes the generated timetable to CSV files. Additionally, the program provides functionalities to generate timetables for specific professors or semesters and also allocates Elective courses, facilitating efficient scheduling and management within an educational institution. The core functionality revolves around allocating courses to available time slots while considering various constraints, such as professor availability, credit requirements, and branch-specific arrangements, thus automating the process of timetable generation in an academic setting.

## How to Run?

   timetablegenerator(Final).cpp , winter.txt, autumn.txt, winter_elective.txt, autumn_elective, these all files should be in one folder. Run the timetablegenrator(final).cpp file and output file will be saved in same folder. Here winter.txt, autumn.txt, winter_elective.txt, autumn_elective.txt are input files.

## Work Distribution

   Deep created all input files and takes input from that files to store in different vectors.Parth created function which allocates courses in specific slots and from that function one function is called named "Is_Prof_Avail" to check whether professor is available or not in that specific slot was made by Heet. Printing timetable in CSV file was done by Om.
      Other additional functionality like Professor Timetable, Semester Timetable and Elective Timetable was combined input of all the group members. Algorithm of this code is also created by our group members without any reference. 

## Group Members

[PARTH566DA](https://github.com/PARTH566DA)

[HRT005](https://github.com/HRT005)

[OmPatel1511](https://github.com/OmPatel1511)

[DeepKakadiya6537](https://github.com/DeepKakadiya6537)

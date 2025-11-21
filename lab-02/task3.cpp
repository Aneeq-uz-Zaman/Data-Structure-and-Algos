// Task 3:  Deals with buffered writing!  
// Objective:   
// • The main objective of this is to experience the effect on performance (time) with the use of 
// buffered reading/writing.  
// • Getting the basic concept of indexing and its advantage on performance (time).  
// • Hands on STL.  
// Prerequisite Setup:  
 
// 1. Define a struct ‘Student’ as follows:  
// struct Student 
// { 
//  int roll; 
//  char name[30]; 
//  Student():roll(0) 
//  { 
//   strcpy(name,"none"); 
//  } 
// }; 
// 2. The following code stores 10 million records of ‘Student’ in a file in binary mode pass N 
// = 10000000  
// void addToStudentUnBuffered(int N) 
// { 
//  ofstream  ofs("studentdatabase.txt",ios::binary|ios::out); 
//  Student s;  
//  for (int i=1; i<N; i++) 
//  { 
//   s.roll = i; 
//   ofs.write((char*)(&s),sizeof(Student)); 
//  } 
//  ofs.close(); 
// } 
// 3. Write the following code in main:  [Required header files stdio.h and windows.h]   
 
// SYSTEMTIME systime;  
// cout<<"\nWriting Records to File one by one";  
// GetLocalTime(&systime);  
// cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systi
//  me.wMilliseconds;  
// addToStudentUnBuffered();  
// GetLocalTime(&systime);  
// cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systi
//  me.wMilliseconds; 
  
// Can you improve the performance of addToStudentUnBuffered ?  
// Idea is to go for buffered writing. Name your function as addToStudentBuffered  
// Task 4: Deals with buffered reading!  
  
// Write a function which display all the Student records stored in "studentdatabase.txt" in Task-3.  
// [Maybe you noticed or not: its 343 MB file]  
 
// Note: Write two versions of display all records as follows:  
  
// ➔ readAllRecordsUnBuffered() //:It reads records from file one by one i.e. unbuffered.  
// ➔ readAllRecordsBuffered() //:It reads records from file in a buffer.  
  
// Then observe the response time of both functions by getting the system time.


#include<fstream>
#include<iostream>
#include<string>
#include"windows.h"
#include "stdio.h"

using namespace std;

struct Student 
{ 
 int roll; 
 char name[30]; 
 Student():roll(0) 
 { 
  strcpy(name,"none"); 
 } 
}; 
void addToStudentUnBuffered(int N) 
{ 
 ofstream  ofs("studentdatabase.txt",ios::binary|ios::out); 
 Student s;  
 for (int i=1; i<N; i++) 
 { 
  s.roll = i; 
  ofs.write((char*)(&s),sizeof(Student)); 
 } 
 ofs.close(); 
} 
void addToStudentBuffered(int N) 
{ 
ofstream  ofs("studentdatabase.txt",ios::binary|ios::out); 
Student s;
int array[20000];
for (int i=1; i<N; i++) 
{ 
    for(int j=0;j<20000;j++)
    {
        array[j]=j;
    }
    
    ofs.write((char*)(&s),sizeof(Student)*20000); 
} 
 ofs.close(); 
} 

int main()
{
    
    SYSTEMTIME systime;  
    cout<<"\nWriting Records to File one by one";  
    GetLocalTime(&systime);  
    cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systime.wMilliseconds;  
    addToStudentUnBuffered(1000000);  
    GetLocalTime(&systime);  
    cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systime.wMilliseconds; 
        


    return 0;
}
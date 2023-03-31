#include <sys/wait.h>
#include <time.h>
#include <ncurses.h>
#include <dirent.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

WINDOW *createa_newwin(int height, int width, int startX, int startY);
void updateStatusWindow(char* path, char* name);
void DestroyALL();
bool updateLeftWindow(char* currentPath);
int currentFilesLeft;
int currentFilesRight; 

char* currentFiles1; // left window
char* currentFiles2; // right window 
char* currentFilesInFolders(char* nameFoldersPath, int numberFiles);
int currentNumberFilesInFolder(char* nameDirPath);

WINDOW* my_winlos;
WINDOW* my_winlos2;
WINDOW* my_winStatus;

const char* stringDot = ".";
const char* stringTwoDot = ".."; 

char* leftListNames[100];
char* rightListNames[100];


int cSEle; // current Selected Element;


int main (void){

   int ch;     
  // WINDOW* my_winlos;
  // WINDOW* my_winlos2;
   initscr();
   start_color();
   noecho();
   curs_set(0);
   cSEle = 1; 
 
   DIR* folder;
   struct dirent* entry;
   int files = 0;
   folder = opendir(".");
  
  init_pair(1, COLOR_RED, COLOR_WHITE); 
 
   if( folder == NULL ){
   printw(" not ok open ");
   exit(1);
   
 }  else {
   
 // attron(COLOR_PAIR(1));  
 // printw(" ok opens all "); // ok print red color 
 // attroff(COLOR_PAIR(1));  
    
  while( ( entry = readdir(folder)) )
  {
     files++;
     currentFilesLeft++;
     currentFilesRight++;
     
      
     
   //printw(" File %3d: %s\n ", files, entry->d_name);
  }

   char *lStringArrayName[currentFilesLeft];
 
   while( ( entry = readdir(folder)) )
  {
     strcpy(lStringArrayName[0], entry->d_name);
  }
 }

  closedir(folder);
      
   keypad(stdscr, TRUE);
   curs_set(0);
   init_pair(2, COLOR_BLUE, COLOR_WHITE);
   refresh();
 
     

   int h, w, s1, s2;
   h = LINES - 4;  //2; // LINES - 2; // was 3
  
   w = (COLS / 2) - 2;
   s1  = LINES / 2; 
   //wprintw() 
 
 
      // LINES 29 
      // COLUMNS 100   
      s2 = (COLS - w )/ 2;
      printw( " my lines = %d ", LINES);
      printw(" my COLUMNS = %d \n", COLS);   
      init_pair(2, COLOR_BLUE, COLOR_WHITE);
      init_pair(3, COLOR_RED, COLOR_CYAN);
      my_winlos = createa_newwin(h, w, 0, 1);
      my_winlos2  = createa_newwin(h, w, 0, ( COLS / 2) + 2);
      my_winStatus = createa_newwin(3, COLS - 2, LINES - 3, 1);
      wbkgd(my_winlos, COLOR_PAIR(2));
      wbkgd(my_winlos2, COLOR_PAIR(2));
     
      refresh();
      wrefresh(my_winlos2);      
  
       //wattron(my_winlos, A_BOLD);
       wattron(my_winlos, COLOR_PAIR(2));
       attron(COLOR_PAIR(2));
      
       wrefresh(my_winlos);
       wattroff(my_winlos, COLOR_PAIR(0)); 

     
 
       wbkgd(my_winStatus, COLOR_PAIR(3));
       wattron(my_winStatus, COLOR_PAIR(3));
       wrefresh(my_winStatus);
       wattroff(my_winStatus, COLOR_PAIR(3));     
       char* myName = "Los";

       // wprintw(my_winlos, "%d \n", 200);
       // mvwprintw(my_winlos, 1, 2, "%d \n", 200);
    
     char cwd[256];
     if(getcwd(cwd, sizeof(cwd)) == NULL ){
       // no files 
       exit(1);
      }   

      int currentFilesLeftWindow = currentNumberFilesInFolder(cwd);
      //char* filesLeft = currentFilesInFolders(cwd, currentFilesLeftWindow);
 
      // printMyCurrent in folder's 
   
     // mvprintw(1, 2, "files in folders %d ", currentFilesLeftWindow);  // 11  
      
   
     // update left Window(); 
     // update right Window();
 
      if(!updateLeftWindow(cwd)){
        printf(" no create left window ! \n");
        exit(1);
    }

      for(int i = 0; i < currentFilesLeftWindow; i++){
  
  
        //if()
    

        
      // mvprintw(2+i, 2, "%s", &filesLeft[i]);  
     	 
         //mvprintw(2, 2, "%s", &filesLeft[0]);
    	 //mvprintw(3, 2, "%s", &filesLeft[1]);
   	 //mvprintw(4, 2, "%s", &filesLeft[2]);
   	 //mvprintw(5, 2, "%s", &filesLeft[3]);     
 
 
   } 

       attroff(COLOR_PAIR(2)); 
       wrefresh(my_winlos);
       //mvprintw(12, 2, "New names "); // 12  
   
      // another side
       attron(COLOR_PAIR(2)); 
      // mvprintw(1, (COLS/2) + 3, "new sides");       

       refresh();
       wrefresh(my_winlos);
       wrefresh(my_winlos2); 
       char* nameTest = "simple.c";
      // updateStatusWindow(nameTest);
      // wrefresh(my_winStatus);    


 while(1) { 
   
    ch = getch();
   //printf("KEY NAME : %s - %d\n", keyname(ch),ch);
   if( ch == KEY_F(1)){
  //   printw("F1 pressed ");
   } else {
   
   if(ch == KEY_LEFT){
   //printw(" los key LEFT ");
   }
   
  if (ch == KEY_UP){
    cSEle--;
    updateLeftWindow(cwd);  
 }  
 
  if (ch == KEY_DOWN){
    cSEle++; 
    updateLeftWindow(cwd); 
  } 
 
  if( ch == 10 ){ // ENTER
  
  } 

  if( ch == 9 ){  // TAB
   
 } 
  if (ch == 113 ){ 
  
   DestroyALL();
   endwin();
   exit(1); 
 }
  
   if(ch == 27){ 
   
   DestroyALL();  
   endwin();
   exit(1);
     }
   }
}  // end While  
    DestroyALL(); 
    endwin();
    return 0;
}

 
//char* currentFiles1; // left window
//char* currentFiles2; // right window
char* currentFilesInFolders(char* nameFoldersPath, int numberFiles){
 
   char* myName[numberFiles]; //= malloc(sizeof(char) * numberFiles);
  // char* myName = (char*) calloc(numberFiles, sizeof(char[128]));
   struct dirent* files;
   DIR* dir = opendir(nameFoldersPath); // was "."
   if( dir == NULL ){
    printf(" not open DIR ");
    return myName[0];
    }

  int i = 0;
  while( (files = readdir(dir)) != NULL){
  
   myName[i] = files->d_name;
   i++;
    
  }
    
  return myName[0];
}


 

char* returnFilesNames(char* path, int number ){
  
   char* returnNamesString[1];  
   char* globalMemoryString = (char*)calloc(2, sizeof(char*));
   if(globalMemoryString == NULL ){
     return ""; 
  }  
 
 
   struct dirent* files;
   DIR* dir = opendir(path);
   if( dir == NULL ){
    printf(" not open DIR ");
    return "";
    }

   memset(globalMemoryString, '\0', 24);
   
  int ii = 0;
  while( (files = readdir(dir)) != NULL){
   if(ii == number){   
   memcpy(globalMemoryString,files->d_name, 24);
  }
   
   ii++;
  }   
 return globalMemoryString; 
 } 


bool  updateLeftWindow(char* currentPath){
   
  int nStep = 0;
//   char* leftListNames[100];
//  char* rightListNames[100];
   for(int i = 0; i < 100; i++){
    leftListNames[i] = "\n";  
 }  
    
    //if(checkUpPathIsFolder(currentPath)){
     leftListNames[0] = "..";
  //}
   
  
       mvprintw(1 + nStep, 2, "%s", leftListNames[0]);
       nStep++;
   
     
      int number = currentNumberFilesInFolder(currentPath);   
  

    // cSEle
    for(int i = 0; i < number; i++){
    char* currentNa = returnFilesNames(currentPath, i);
    
    if( strcmp(currentNa, stringTwoDot) == 0 ){
    }else if (strcmp(currentNa, stringDot) == 0) {
  } else {
     
     if(nStep == cSEle){
    attron( COLOR_PAIR(1)); // was my_winlos
     mvprintw(1+nStep, 2, "%s", currentNa);
    attroff(COLOR_PAIR(1));
  
    updateStatusWindow(currentPath,currentNa);
 
   }else {
     attron(COLOR_PAIR(2));   
    mvprintw(1+nStep, 2, "%s", currentNa);
     attroff(COLOR_PAIR(2));
   }
     
      
   //  wbkgd(my_winlos, COLOR_PAIR(2));

     nStep++;
   } 
 }
 
  refresh();     
  wrefresh(my_winlos);
         
 
  return true;
 }

int currentNumberFilesInFolder(char* nameDirPath){
  
   int numberFile = 0;
   struct dirent* files;
   DIR* dir = opendir(nameDirPath);
   if( dir == NULL ){
    printf(" not open DIR ");
    return 0;
    }

  while( (files = readdir(dir)) != NULL){

   //myName[numberFile] = files->d_name;
   //printf("%s \n", files->d_name);
    numberFile++;
   }
 
 return numberFile;
 } 

void DestroyALL(){
 

 }





void updateStatusWindow(char* cwd, char* name)
{
  
   attron(COLOR_PAIR(3));
  
  char cwdTemp[40]; 
  strcpy(cwdTemp, cwd);
    
  char* ptr2 = strcat(cwdTemp, "/");
  char* ptr3 = strcat(cwdTemp, name);
 // printf(" my final files == %s \n" , cwd);

  char date[20];
  struct stat ta2;
  stat(cwdTemp, &ta2);
  
   strftime(date, 20, "%d-%m-%y", localtime(&(ta2.st_ctime)));
   mvprintw(LINES - 2, 2, "%s    %ldKB    %s ", name, ta2.st_size,date);

   attroff(COLOR_PAIR(3));
    wrefresh(my_winStatus);
}


WINDOW* createa_newwin(int height, int width, int startX, int startY){
 
 WINDOW* local_win;
 local_win = newwin(height, width, startX, startY);
 box(local_win, 0, 0);

 wrefresh(local_win);
 return local_win; 
}


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
bool updateLeftWindow(char* currentPath, bool needUpdate);
int currentFilesLeft;
int currentFilesRight; 
bool checkUpPathIsFolder(char* currentPath);
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
int currentLeftElementsInFolder;
int currentRightElementsInFolder;
char* cNamesSelected; 
char* cwdLEFT;

char* returnFilesNames(char* path, int number );

int main (void){

   int ch;     
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
       
  while( ( entry = readdir(folder)) )
  {
     files++;
     currentFilesLeft++;
     currentFilesRight++;
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
 
      // LINES 29 
      // COLUMNS 100   
      s2 = (COLS - w )/ 2;
      //printw( " my lines = %d ", LINES);
      //printw(" my COLUMNS = %d \n", COLS);   
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
    
       char cwd[256];
       if(getcwd(cwd, sizeof(cwd)) == NULL ){
       // no files 
        exit(1);
      }   

      int currentFilesLeftWindow = currentNumberFilesInFolder(cwd);
      
      if(!updateLeftWindow(cwd, false)){
        printw(" no create left window ! \n");
        exit(1);
    }

       attroff(COLOR_PAIR(2)); 
       wrefresh(my_winlos);
       attron(COLOR_PAIR(2));        

       refresh();
       wrefresh(my_winlos);
       wrefresh(my_winlos2);

 while(1) { 
   
    ch = getch();
   
   if( ch == KEY_F(1)){

   } else {
   
   if(ch == KEY_LEFT){
 
   }
   
  if (ch == KEY_UP){
 
   if( cSEle - 1 <= 0){
     cSEle = 0;
  }else {
    cSEle--; 
  }
    
    updateLeftWindow(cwd, false);  
 }  
 
  if (ch == KEY_DOWN){
  
   if( cSEle + 1 >= currentLeftElementsInFolder){
        cSEle =  currentLeftElementsInFolder;
   } else {
      cSEle++;
   }    
   
    updateLeftWindow(cwd, false); 
  } 
 
  if( ch == 10 ){ // ENTER
     
         char tempCWD[256];
         strncpy(tempCWD, cwd, sizeof(cwd));

         strcat(tempCWD, "/");
         strcat(tempCWD, cNamesSelected);
         struct stat l_info;
 
   
     if ( strcmp(cNamesSelected, stringTwoDot) == 0 ){
         char newCWD[256];
         strncpy(newCWD, cwd, sizeof(cwd));    
        
          char* ptr1;
          int ch = '/';
          ptr1 = strrchr(newCWD, ch);        
          char* nCWD;
          strncat(nCWD, newCWD, strlen(cwd) - strlen(ptr1));
          cSEle = 0;
          updateLeftWindow(nCWD, true);
      
        } else if ( stat(tempCWD, &l_info) != 0){
        
        } else if(l_info.st_mode & S_IFDIR){
                
          
     //int allocate = snprintf(NULL, 0, "%s", files->d_name);
     //globalTime = malloc(allocate + 1);
    // snprintf(globalTime, allocate + 1, "%s", files->d_name);
      //  cwd = &tempCWD;
       //  strcpy(cwd, tempCWD);
         updateLeftWindow(tempCWD, true);     
          
       } else {
          //  printf(" no this directory \n");
       }
        
   } else 
  {
  }
   
 //if( stat(tempCWD, &l_info) == 0 && l_info.st_mode & S_IXUSR){
     
  //  pid_t forkLos;
  //  forkLos = fork();

  //if( forkLos == 0){
  //  sleep(1);
  //  char* args[] = {" test calling", NULL};
     // "/home/loskutnikovlemp3/test22/./outLos"
  //  execv(tempCWD, args);
  // }  else if (forkLos != -1){
  //wait(NULL);
  //printf(" parent  precedure is now goint exit \n");

 //  } else {
 // printf("error occured is calling fork");
 //  }
 // } 
// } 

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
 
   char* myName[numberFiles];
   struct dirent* files;
   DIR* dir = opendir(nameFoldersPath); // was "."
   if( dir == NULL ){
    printw(" not open DIR ");
    return myName[0];
    }

  int i = 0;
  while( (files = readdir(dir)) != NULL){
  
   myName[i] = files->d_name;
   i++;
    
  }
  closedir(dir);  
  return myName[0];
}


 

char* returnFilesNames(char* path, int number ){
  
  // char* returnNamesString[1];  
  // char* globalMemoryString = calloc(2, 16);
  // if(globalMemoryString == NULL ){
    // return ""; 
 // }  

 
  //int allocate = snprintf(NULL, 0, "%s", ) 
 
     char* globalTime;
     struct dirent* files;
     DIR* dir = opendir(path);
    if( dir == NULL ){
      printw(" not open DIR ");
      return "";
      }

   //memset(globalMemoryString, '\0', 16);
  
    //char* globalMemoryString;  
   int ii = 0;
   while( (files = readdir(dir)) != NULL){
   
   if(ii == number){ 
  
  // size_t mySize = strlen(files->d_name);
  // char returnNamesString[mySize];
   //globalMemoryString = calloc(mySize + 1, sizeof(char));
 //  if(globalMemoryString == NULL ){
   //  return "";
  //}
  
     int allocate = snprintf(NULL, 0, "%s", files->d_name);  
     globalTime = malloc(allocate + 1);
     snprintf(globalTime, allocate + 1, "%s", files->d_name);
 
  //  strcpy(globalMemoryString, files->d_name);
    
   //  memcpy(globalMemoryString,files->d_name, sizeof(files->d_name));
    }
     
     ii++;
    }   
   closedir(dir); 
    return globalTime;
   //return globalMemoryString; 
 } 


bool  updateLeftWindow(char* currentPath, bool needUpdate){
  
 
   int nStep = 0;
   
  if(needUpdate){
  
 // currentLeftElementsInFolder
     
     attron(COLOR_PAIR(2)); 
    for(int d = 0; d < currentLeftElementsInFolder; d++) {
     mvprintw(1 + nStep, 2, "%s", "");
      nStep++;
 }

     attroff(COLOR_PAIR(2));
     wrefresh(my_winlos);
     refresh();
 }  
     nStep = 0;   
    
    
    if(checkUpPathIsFolder(currentPath)){
     leftListNames[0] = "..";
     

    if(cSEle == 0)  {
    attron( COLOR_PAIR(1)); // was my_winlos  
    mvprintw(1 + nStep, 2, "%s", leftListNames[0]);
    attroff(COLOR_PAIR(1));
     
    cNamesSelected = leftListNames[0];
    //updateStatusWindow(currentPath,);

   } else {
     attron(COLOR_PAIR(2));
     mvprintw(1 + nStep, 2, "%s", leftListNames[0]);
     attroff(COLOR_PAIR(2));
   }   
      nStep++;
 }
     
  
    int number = currentNumberFilesInFolder(currentPath);   
  
    // cSEle
    // currentLeftElementsInFolder 

    //printw(" my number %d and %d  \n", number , currentLeftElementsInFolder);
    for(int i = 0; i < number; i++){
    char* currentNa; 
   if ( !needUpdate ){
    currentNa = returnFilesNames(currentPath, i); 
   }else {
    currentNa = "sdfsdf";   
    } 
    
    //  = returnFilesNames(currentPath, i);
    // char* currentNa = "sdfsdf";
    if( strcmp(currentNa, stringTwoDot) == 0 ){
    }else if (strcmp(currentNa, stringDot) == 0) {
  } else {
     
     if(nStep == cSEle){
     attron( COLOR_PAIR(1)); // was my_winlos
     mvprintw(1+nStep, 2, "%s", currentNa);
     attroff(COLOR_PAIR(1));
  
     updateStatusWindow(currentPath,currentNa);
     cNamesSelected = currentNa;
    // free(currentNa);
   }else {
     attron(COLOR_PAIR(2));   
     mvprintw(1+nStep, 2, "%s", currentNa);
     attroff(COLOR_PAIR(2));
    // free(currentNa);
   }
     
   // free (currentNa);

     nStep++;
   } 
 }
 
 currentLeftElementsInFolder = nStep - 1;
  refresh();     
  wrefresh(my_winlos);
         
 
  return true;
 }

int currentNumberFilesInFolder(char* nameDirPath){
  
   int numberFile = 0;
   struct dirent* files;
   DIR* dir = opendir(nameDirPath);
   if( dir == NULL ){
    printw(" not open DIR ");
    return 0;
    }

  while( (files = readdir(dir)) != NULL){

   //myName[numberFile] = files->d_name;
   //printf("%s \n", files->d_name);
    numberFile++;
   }

  
   closedir(dir);
 return numberFile;
 } 

void DestroyALL(){
 
   wrefresh(my_winlos);
   wrefresh(my_winlos2);
   wrefresh(my_winStatus);
   
   delwin(my_winlos);
   delwin(my_winlos2);
   delwin(my_winStatus); 
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
   mvprintw(LINES - 2, 2, " %s    %ldKB    %s ", name, ta2.st_size,date);

   attroff(COLOR_PAIR(3));
   //free (ptr2);
   //free (ptr3);
   wrefresh(my_winStatus);
}


WINDOW* createa_newwin(int height, int width, int startX, int startY){
 
 WINDOW* local_win;
 local_win = newwin(height, width, startX, startY);
 box(local_win, 0, 0);

 wrefresh(local_win);
 return local_win; 
}




bool checkUpPathIsFolder(char* currentPath){
    
 
 return true;
 }


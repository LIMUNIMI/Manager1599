/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerGeneral.h
 * Author: Ale
 *
 * Created on 31 agosto 2020, 17.36
 */

#ifndef MANAGERGENERAL_H
#define MANAGERGENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

//Description
struct author{
    char* name;
    char* type;
    struct author* next_author;
};

struct other_title{
    char* title_value;
    struct other_title *next_title;
 };
 
 struct date{
    char* date_value;
    char* type;
    struct date* next_date;
 };
 
 struct genre{//?
      char* name;//REQUIRED
      char* description;
      char* weight;
      struct genre* next_genre;
 };

struct description{
  int n_authors;
  int n_other_titles;
  int n_dates;
  int n_genres;
  
  char* main_title;//1
  char* number;//?
  char* work_title;//?
  char* work_number;//?
  struct author* authors;//*
  struct other_title* other_titles;//*
  struct date* dates;//*
  struct genre* genres;//1
};

//Realted Files
struct related_file{//EMPTY
  char* file_name;//REQUIRED
  char* file_format;//REQUIRED
  char* encoding_format;//REQUIRED
  char* description;
  char* copyright;
  char* notes;
  //start_event_ref;
  //end_event_ref;
  struct related_file *next_file;
};

//Analog Media
struct analog_medium{//EMPTY
    char* description;//REQUIRED
    char* copyright;
    char* notes;
    struct analog_medium* next_medium;
};


//Livello General
struct general{
    int n_related_files;
    int n_analog_media;
    
    struct description description;
    struct related_file* related_files;
    struct analog_medium* analog_media;
    char* notes;
};

//Variables
struct general general_layer;

//Prototypes
void loadGeneral();
void loadDescription();
void loadRelatedFiles();
void loadAnalogMedia();
void loadNotes();

void printDescription();
void printRelatedFiles();
void printAnalogMedia();
void printNotes();


#ifdef __cplusplus
}
#endif

#endif /* MANAGERGENERAL_H */


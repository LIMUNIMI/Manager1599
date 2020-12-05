/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerGeneral.h
 * Author: Alessandro Talamona
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
    xmlChar* name;
    xmlChar* type;
    struct author* next_author;
};

struct other_title{
    xmlChar* title_value;
    struct other_title *next_title;
 };
 
struct date{
    xmlChar* date_value;
    xmlChar* type;
    struct date* next_date;
 };

struct description{
  int n_authors;
  int n_other_titles;
  int n_dates;
  int n_genres;
  
  xmlChar* main_title;//1
  xmlChar* number;//?
  xmlChar* work_title;//?
  xmlChar* work_number;//?
  struct author* authors;//*
  struct other_title* other_titles;//*
  struct date* dates;//*
  struct genre* genres;//1
};

//Realted Files
struct related_file{//EMPTY
  xmlChar* file_name;//REQUIRED
  xmlChar* file_format;//REQUIRED
  xmlChar* encoding_format;//REQUIRED
  xmlChar* description;
  xmlChar* copyright;
  xmlChar* notes;
  xmlChar* start_event_ref;
  xmlChar* end_event_ref;
  
  struct related_file *next_file;
};

//Analog Media
struct analog_medium{//EMPTY
    xmlChar* description;//REQUIRED
    xmlChar* copyright;
    xmlChar* notes;
	
    struct analog_medium* next_medium;
};


//Livello General
struct general{
    int n_related_files;
    int n_analog_media;
    
    struct description description;
    struct related_file* related_files;
    struct analog_medium* analog_media;
    xmlChar* notes;
};

//Variables


//Prototypes
MANAGERIEEE1599_API struct general loadGeneral();
MANAGERIEEE1599_API void loadDescription();
MANAGERIEEE1599_API void loadRelatedFiles();
MANAGERIEEE1599_API void loadAnalogMedia();
MANAGERIEEE1599_API void loadNotes();

MANAGERIEEE1599_API void printGeneral();
MANAGERIEEE1599_API void printDescription();
MANAGERIEEE1599_API void printRelatedFiles();
MANAGERIEEE1599_API void printAnalogMedia();
MANAGERIEEE1599_API void printNotes();


#ifdef __cplusplus
}
#endif

#endif /* MANAGERGENERAL_H */


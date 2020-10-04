/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.h
 * Author: Ale
 *
 * Created on 26 agosto 2020, 22.08
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <string.h>

struct rights{
    char* file_name;
};

struct genre{//?
     char* name;//REQUIRED
     char* description;
     char* weight;

     struct genre* next_genre;
};
    
xmlChar *docname;
xmlDocPtr doc;
char* file_name;
char* encoding;

xmlDocPtr getDoc(xmlChar *file_name);
xmlXPathObjectPtr getNodeset(xmlDocPtr doc, xmlChar *xpath);
char* concat(const char *s1, const char *s2);  
int xmlCharToInt(xmlChar* string);

struct rights loadRights(xmlNodePtr cur);
struct genre* loadGenre(xmlNodePtr cur);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */


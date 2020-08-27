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
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <string.h>
    
xmlChar *docname;
xmlChar *docpath;
xmlDocPtr doc;

xmlDocPtr getDoc(xmlChar *docpath);
xmlXPathObjectPtr getNodeset(xmlDocPtr doc, xmlChar *xpath);
char* concat(const char *s1, const char *s2);    

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */


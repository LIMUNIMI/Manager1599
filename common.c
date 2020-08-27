/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "common.h"

xmlDocPtr getDoc(xmlChar *docpath){
    xmlDocPtr doc;
    xmlNodePtr cur; 
    
    doc=xmlParseFile(docpath);
    if(doc==NULL){
        fprintf(stderr,"Error during document parsing\n");
        return NULL;
    }
    
    cur=xmlDocGetRootElement(doc);
    if(cur==NULL){
        fprintf(stderr,"Empty document\n");
        xmlFreeDoc(doc);
        return NULL;
    }
    
    if(xmlStrcmp(cur->name,(const xmlChar*)"ieee1599")){
        fprintf(stderr,"Document is not ieee1599\n");
        xmlFreeDoc(doc);
        return NULL;
    }   
 
    return doc;
}

xmlXPathObjectPtr getNodeset(xmlDocPtr doc, xmlChar *xpath){
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;
    
    context=xmlXPathNewContext(doc);
    if(context==NULL){
        fprintf(stderr,"Error in xmlXPathNewContext - getNodeset\n");
        return NULL;
    }
    result=xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if(result==NULL){
        fprintf(stderr,"Error in xpath evaluation - getNodeset\n");
        return NULL;
    }
    
    printf("Executed xpath:%s\n",xpath);
    
    return result;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}
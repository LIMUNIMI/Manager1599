/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "common.h"

xmlDocPtr doc;
xmlChar* file_root_folder = "./File/";
xmlChar* dtd_root_folder = "./File/DTD/";

int isValid(xmlDocPtr doc) {// return 1 if document is valid

    int res = 0;

    xmlValidCtxtPtr ctxt = xmlNewValidCtxt();
    xmlDtdPtr dtd= xmlParseDTD(NULL, (const xmlChar*)(concat((const char*)getDtdRootFolder(),(const char*)"ieee1599.dtd")));

    if (dtd == NULL)
        fprintf(stderr, "Cant't load DTD\n");
    else
        res=xmlValidateDtd(ctxt,doc,dtd);

    return res;
}

int getDoc(xmlChar* docpath){// return 1 if no errors occurred

    int no_error = 1;

    xmlNodePtr cur;

    doc=xmlParseFile((char*)docpath);
    if(doc==NULL){
        fprintf(stderr,"Error during document parsing\n");
        no_error=0;
    }
    else {
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) {
            fprintf(stderr, "Empty document\n");
            xmlFreeDoc(doc);
            no_error = 0;
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*)"ieee1599")) {
            fprintf(stderr, "Document is not ieee1599\n");
            xmlFreeDoc(doc);
            no_error = 0;
        }
        else if (isValid(doc) == 0) {
            fprintf(stdout, "Document is not Valid\n");
            xmlFreeDoc(doc);
            no_error = 0;
        }
    }

    return no_error;
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

char* concat(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    if (result != 0){
        strcpy(result,s1);
        strcat(result,s2);
    }

    return result;
}

int xmlCharToInt(xmlChar* string){
    int value=0;
    
    if(string!=NULL)
        value = atoi((const char*)string);//return 0 if not valid string

    return value;
}

double xmlCharToDouble(xmlChar* string){
    double value = 0;
    
    if (string != NULL)
        value = atof((const char*)string);// retrun 0 if not valid string

    return value;
}

struct rights loadRights(xmlNodePtr cur){
    struct rights value = {""};
    xmlAttr* attributes;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
            value.file_name=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }

    return value;
}

struct genre* loadGenre(xmlNodePtr cur){
    struct genre* value=(struct genre*)malloc(sizeof(struct genre));
    value=calloc(1,sizeof(struct genre));
    xmlAttr* attributes;

    if (value) {
        value->next_genre = NULL;
        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"name")) {
                value->name = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"weight")) {
                value->weight = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }
    }
    else { fprintf(stderr, "Memory allocation failed for 'genre' element\n"); }

    return value;
}

void clean() {
      
    //xmlFreeDoc(doc);
    xmlCleanupParser();

}

MANAGERIEEE1599_API void setFileRootFolder(xmlChar* new_file_root_folder) {
    file_root_folder = new_file_root_folder;
}
MANAGERIEEE1599_API void setDtdRootFolder(xmlChar* new_dtd_root_folder) {
    dtd_root_folder = new_dtd_root_folder;
}
MANAGERIEEE1599_API xmlChar* getFileRootFolder() {
    return file_root_folder;
}
MANAGERIEEE1599_API xmlChar* getDtdRootFolder() {
    return dtd_root_folder;
}

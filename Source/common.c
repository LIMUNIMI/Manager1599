/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "common.h"

xmlChar *docname;
xmlDocPtr doc;
char* file_name;

int validate(xmlDocPtr doc) {

    int res = 0;
    xmlValidCtxtPtr ctxt = xmlNewValidCtxt();
    xmlNodePtr dtd= xmlParseDTD(NULL, (const xmlChar*)"./File/DTD/ieee1599.dtd");
    if (dtd == NULL)
        fprintf(stderr, "Cant't load DTD\n");
    else
        res=xmlValidateDtd(ctxt,doc,dtd);
    return res;
}

xmlDocPtr getDoc(xmlChar* docpath){

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc=xmlParseFile((char*)docpath);
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
    int error=0;

    for(int i=xmlStrlen(string)-1;i>=0;i--){
        if (string[i]>='0'&&string[i]<='9'){
            value+=(int)pow(10,xmlStrlen(string)-(int)1-i)*((int)string[i]-(int)48);
        }
        else{error=1;}
    }
    if(error){
        value=-1;
        fprintf(stderr,"Can't convert string '%s' to integer\n",string);
    }

    return value;
}

struct rights loadRights(xmlNodePtr cur){
    struct rights value;
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

    value->next_genre=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"name")){
            value->name=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
            value->description=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"weight")){
            value->weight=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }

    return value;
}

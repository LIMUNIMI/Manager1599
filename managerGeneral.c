/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "common.h"

//Description
struct author{
    char* name;
    char* type;
};

struct genre{//EMPTY
    char* name;//REQUIRED
    char* description;
    char* weight;
};

struct description{
  char* main_title;//1
  char* number;//?
  char* work_title;//?
  char* work_number;//?
  struct authors{//*
      struct author author_value;
      struct authors *next_author;
  };
  struct other_title{//*
      char* title_value;
      struct other_title *next_title;
  };
  struct date{//*
      char* date_value;
      struct date* next_date;
  };
  struct genres{//?
      struct genre genre_value;
      struct genres* next_genre;
  };
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
  // end_event_ref;
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
    struct description description;
    struct related_file* related_files;
    struct analog_medium* analog_media;
    char* notes;
};

//Variables
struct general general_layer;

//Prototypes
void loadGeneral();
void loadNotes();
void loadAnalogMedia();
void loadRelatedFiles();
void loadDescription();

//Functions
void loadGeneral(){ 

    //inizializzare general_layer
    
    loadDescription();
    loadRelatedFiles();
    loadAnalogMedia();
    loadNotes();
    
}

void loadNotes (){
    
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    
    xpath=(xmlChar *)"/ieee1599/general/notes";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        while(cur!=NULL){
            if(xmlStrcmp(cur->name,(const xmlChar*)"text")){
                if(!xmlStrcmp(cur->name,(const xmlChar*)"notes")){
                    if(xmlNodeListGetString(doc,cur->xmlChildrenNode,1)!=NULL){
                        general_layer.notes=xmlNodeListGetString(doc,cur->xmlChildrenNode,1); 
                    }
                }
            }
            cur=cur->next;
        }
    }
    
    printf("Notes: %s\n",general_layer.notes);
}

void loadAnalogMedia (){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct analog_medium *head=NULL;
    struct analog_medium *temp=NULL;
    struct analog_medium *p=NULL;
    xpath=(xmlChar *)"/ieee1599/general/analog_media/analog_medium";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){
            cur=nodeset->nodeTab[i];
            if(!xmlStrcmp(cur->name,(const xmlChar*)"analog_media")){
                temp=(struct  analog_medium*)malloc(sizeof(struct analog_medium));
                temp=calloc(1,sizeof(struct analog_medium));
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                        temp->description=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"copyright")){
                        temp->copyright=xmlGetProp(cur,attributes->name);
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"notes")){
                        temp->notes=xmlGetProp(cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                temp->next_medium=NULL;
                if(head==NULL){
                    head=temp;
                }
                else{
                    p=head;
                    while(p->next_medium!=NULL)
                        p=p->next_medium;
                    p->next_medium=temp;
                }
            }
        }
        general_layer.analog_media=head;
    }   
    
    p=general_layer.analog_media;
    while(p!=NULL){
        printf("Medium: %s %s %s\n",p->copyright,p->description,p->notes);
        p=p->next_medium;
    }
    
}

void loadRelatedFiles (){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct related_file *head=NULL;
    struct related_file *temp=NULL;
    struct related_file *p=NULL;
    xpath=(xmlChar *)"/ieee1599/general/related_files/related_file";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){
            cur=nodeset->nodeTab[i];
            if(!xmlStrcmp(cur->name,(const xmlChar*)"related_file")){
                temp=(struct related_file*)malloc(sizeof(struct related_file));
                temp=calloc(1,sizeof(struct related_file));
                attributes=cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
                        temp->file_name=xmlGetProp(cur,attributes->name); 
                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_format")){
                        temp->file_format=xmlGetProp(cur,attributes->name);

                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"encoding_format")){
                        temp->encoding_format=xmlGetProp(cur,attributes->name);

                    }                   
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                        temp->description=xmlGetProp(cur,attributes->name);

                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"copyright")){
                        temp->copyright=xmlGetProp(cur,attributes->name);

                    }
                    else if(!xmlStrcmp(attributes->name,(const xmlChar*)"notes")){
                        temp->notes=xmlGetProp(cur,attributes->name);
 
                    }  
                    /*else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                        temp->notes=xmlGetProp(cur,attributes->name);
                    }
                     else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                        temp->notes=xmlGetProp(cur,attributes->name);
                    }*/
                    attributes=attributes->next;                     
                }  
                temp->next_file=NULL;
                if(head==NULL){
                    head=temp;
                }
                else{
                    p=head;
                    while(p->next_file!=NULL)
                        p=p->next_file;
                    p->next_file=temp;
                }
            }
        }
        general_layer.related_files=head;
    }   
    
    p=NULL;
    p=general_layer.related_files;
    while(p!=NULL){
       printf("File: %s %s %s %s %s %s\n",p->file_name,p->file_format,p->encoding_format,p->description,p->copyright,p->notes);
       p=p->next_file;
    }
}

void loadDescription(){
    
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    xpath=(xmlChar *)"/ieee1599/general/description";
    result=getNodeset(doc,xpath);
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        fprintf(stderr,"Missing Description in General layer\n");
    }
    else{
        nodeset=result->nodesetval;
        cur=nodeset->nodeTab[0];
        cur=cur->xmlChildrenNode;
        while(cur!=NULL){
            if(!xmlStrcmp(cur->name,(const xmlChar*)"main_title")){
                general_layer.description.main_title=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"number")){
                general_layer.description.number=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"work_title")){
                general_layer.description.work_title=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*) "work_number")) {
                general_layer.description.work_number=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"author")){
            
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"other_title")){
            
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"date")){
            
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"genres")){
            
            }
            cur=cur->next;
        }
    }
}

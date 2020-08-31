/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerGeneral.h"

void loadGeneral(){ 
    //inizializzare general_layer
    
    loadDescription();
    loadRelatedFiles();
    loadAnalogMedia();
    loadNotes(); 
    
    printDescription();
    printRelatedFiles();
    printAnalogMedia();
    printNotes();
}

void loadDescription(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;

    struct author *author_head=NULL;
    struct author *author_temp=NULL;
    struct author *author_p=NULL;
    
    struct other_title *other_title_head=NULL;
    struct other_title *other_title_temp=NULL;
    struct other_title *other_title_p=NULL;
    
    struct date *date_head=NULL;
    struct date *date_temp=NULL;
    struct date *date_p=NULL;
    
    xmlNodePtr temp_cur;
    
    struct genre *genre_head=NULL;
    struct genre *genre_temp=NULL;
    struct genre *genre_p=NULL;
    
    general_layer.description.n_authors=0;
    general_layer.description.n_other_titles=0;
    general_layer.description.n_dates=0;
    general_layer.description.n_genres=0;
    
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
                author_temp=(struct author*)malloc(sizeof(struct author));
                author_temp=calloc(1,sizeof(struct author));
                attributes=cur->properties;
                author_temp->name=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                        author_temp->type=xmlGetProp(cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                author_temp->next_author=NULL;
                if(author_head==NULL){
                    author_head=author_temp;
                }
                else{
                    author_p=author_head;
                    while(author_p->next_author!=NULL)
                        author_p=author_p->next_author;
                    author_p->next_author=author_temp;
                }
                general_layer.description.n_authors++;
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"other_title")){
                other_title_temp=(struct other_title*)malloc(sizeof(struct other_title));
                other_title_temp=calloc(1,sizeof(struct other_title));
                other_title_temp->title_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                other_title_temp->next_title=NULL;
                if(other_title_head==NULL){
                    other_title_head=other_title_temp;
                }
                else{
                    other_title_p=other_title_head;
                    while(other_title_p->next_title!=NULL)
                        other_title_p=other_title_p->next_title;
                    other_title_p->next_title=other_title_temp;
                }
                general_layer.description.n_other_titles++;
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"date")){
                date_temp=(struct date*)malloc(sizeof(struct date));
                date_temp=calloc(1,sizeof(struct date));
                attributes=cur->properties;
                date_temp->date_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                while(attributes!=NULL){
                    if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                        date_temp->type=xmlGetProp(cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                date_temp->next_date=NULL;
                if(date_head==NULL){
                    date_head=date_temp;
                }
                else{
                    date_p=date_head;
                    while(date_p->next_date!=NULL)
                        date_p=date_p->next_date;
                    date_p->next_date=date_temp;
                }
                general_layer.description.n_dates++;
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"genres")){
                temp_cur=cur;
                cur=cur->xmlChildrenNode; 
                while(cur!=NULL){
                    if(!xmlStrcmp(cur->name,(const xmlChar*)"genre")){
                        genre_temp=(struct genre*)malloc(sizeof(struct genre));
                        genre_temp=calloc(1,sizeof(struct genre));
                        attributes=cur->properties;
                        while(attributes!=NULL){
                            if(!xmlStrcmp(attributes->name,(const xmlChar*)"name")){
                                genre_temp->name=xmlGetProp(cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                                genre_temp->description=xmlGetProp(cur,attributes->name);
                            }
                            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"weight")){
                                genre_temp->weight=xmlGetProp(cur,attributes->name);
                            }
                            attributes=attributes->next;
                        }
                        genre_temp->next_genre=NULL;
                        if(genre_head==NULL){
                            genre_head=genre_temp;
                        }
                        else{
                            genre_p=genre_head;
                            while(genre_p->next_genre!=NULL)
                                genre_p=genre_p->next_genre;
                            genre_p->next_genre=genre_temp;
                        }
                        general_layer.description.n_genres++;
                    }
                    cur=cur->next;
                }
                cur=temp_cur;
            }
            cur=cur->next;
        }
        general_layer.description.authors=author_head;
        general_layer.description.other_titles=other_title_head;
        general_layer.description.dates=date_head;
        general_layer.description.genres=genre_head;
    }
}

void printDescription(){
    struct author *author_p=NULL;
    struct other_title *other_title_p=NULL;
    struct date* date_p=NULL;
    struct genre* genre_p=NULL;
    
    printf("Title: %s\n",general_layer.description.main_title);
    if(general_layer.description.number!=NULL) printf("Number: %s\n",general_layer.description.number);
    if(general_layer.description.work_title!=NULL) printf("Work Title: %s\n",general_layer.description.work_title);
    if(general_layer.description.work_number!=NULL) printf("Work Number: %s\n",general_layer.description.work_number);
    if(general_layer.description.authors!=NULL){
        author_p=general_layer.description.authors;
        printf("%i authors\n",general_layer.description.n_authors);
        while(author_p!=NULL){
            printf("%s: %s\n",author_p->type,author_p->name);
            author_p=author_p->next_author;
        }
    }
    if(general_layer.description.other_titles!=NULL){
        other_title_p=general_layer.description.other_titles;
        printf("%i other titles\n",general_layer.description.n_other_titles);
        while(other_title_p!=NULL){
            printf("Other title: %s\n",other_title_p->title_value);
            other_title_p=other_title_p->next_title;
        }
    }
    if(general_layer.description.dates!=NULL){
        date_p=general_layer.description.dates;
        printf("%i dates\n",general_layer.description.n_dates);
        while(date_p!=NULL){
            printf("Date: %s\n",date_p->date_value);
            date_p=date_p->next_date;
        }
    }
    if(general_layer.description.genres!=NULL){
        genre_p=general_layer.description.genres;
        printf("%i genres\n",general_layer.description.n_genres);
        while(genre_p!=NULL){
            printf("Genre: %s %s %s\n",genre_p->name,genre_p->description,genre_p->weight);
            genre_p=genre_p->next_genre;
        }
    }
}

void loadRelatedFiles(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct related_file *head=NULL;
    struct related_file *temp=NULL;
    struct related_file *p=NULL;
    
    general_layer.n_related_files=0;
    
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
                general_layer.n_related_files++;
            }
        }
        general_layer.related_files=head;
    }   
}

void printRelatedFiles(){
    struct related_file* p=NULL;
    
    if(general_layer.n_related_files!=0){
        printf("%i related files\n",general_layer.n_related_files);
    }   
    
    p=NULL;
    p=general_layer.related_files;
    while(p!=NULL){
       printf("File: %s %s %s %s %s %s\n",p->file_name,p->file_format,p->encoding_format,p->description,p->copyright,p->notes);
       p=p->next_file;
    }
}

void loadAnalogMedia(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    
    struct analog_medium *head=NULL;
    struct analog_medium *temp=NULL;
    struct analog_medium *p=NULL;
    
    general_layer.n_analog_media=0;
    
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
                general_layer.n_analog_media++;
            }
        }
        general_layer.analog_media=head;
    }       
}

void printAnalogMedia(){
    struct analog_medium *p=NULL;
    
    if(general_layer.n_analog_media!=0){
        printf("%i analog media\n",general_layer.n_related_files);
    }  
    p=general_layer.analog_media;
    while(p!=NULL){
        printf("Medium: %s %s %s\n",p->copyright,p->description,p->notes);
        p=p->next_medium;
    }   
}

void loadNotes(){  
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
}

void printNotes(){ 
    if(general_layer.notes!=NULL)
        printf("Notes: %s\n",general_layer.notes);
}
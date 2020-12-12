/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerGeneral.h"

static struct general general_layer;

struct general loadGeneral(){ 

    loadDescription();
    loadRelatedFiles();
    loadAnalogMedia();
    loadNotes();   

    return general_layer;
}

void printGeneral(){
    
    printf("\n###General Layer###\n");
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
    xmlNodePtr temp_cur;

    struct author *author_head=NULL;
    struct author *author_temp=NULL;
    struct author *author_p=NULL;
    
    struct other_title *other_title_head=NULL;
    struct other_title *other_title_temp=NULL;
    struct other_title *other_title_p=NULL;
    
    struct date *date_head=NULL;
    struct date *date_temp=NULL;
    struct date *date_p=NULL;
    
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
                author_temp= (struct author*)calloc(1, sizeof(struct author));

                if (author_temp) {
                    attributes = cur->properties;
                    author_temp->name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"type")) {
                            author_temp->type = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }
                    author_temp->next_author = NULL;
                    if (author_head == NULL) {
                        author_head = author_temp;
                    }
                    else {
                        author_p = author_head;
                        while (author_p->next_author != NULL)
                            author_p = author_p->next_author;
                        author_p->next_author = author_temp;
                    }
                    general_layer.description.n_authors++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'author' element\n"); }
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"other_title")){
                other_title_temp= (struct other_title*)calloc(1,sizeof(struct other_title));

                if (other_title_temp) {
                    other_title_temp->title_value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    other_title_temp->next_title = NULL;
                    if (other_title_head == NULL) {
                        other_title_head = other_title_temp;
                    }
                    else {
                        other_title_p = other_title_head;
                        while (other_title_p->next_title != NULL)
                            other_title_p = other_title_p->next_title;
                        other_title_p->next_title = other_title_temp;
                    }
                    general_layer.description.n_other_titles++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'other_title' element\n"); }
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"date")){
                date_temp= (struct date*)calloc(1,sizeof(struct date));

                if (date_temp) {
                    attributes = cur->properties;
                    date_temp->date_value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"type")) {
                            date_temp->type = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }
                    date_temp->next_date = NULL;
                    if (date_head == NULL) {
                        date_head = date_temp;
                    }
                    else {
                        date_p = date_head;
                        while (date_p->next_date != NULL)
                            date_p = date_p->next_date;
                        date_p->next_date = date_temp;
                    }
                    general_layer.description.n_dates++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'date' element\n"); }
            }
            else if(!xmlStrcmp(cur->name,(const xmlChar*)"genres")){
                temp_cur=cur;
                cur=cur->xmlChildrenNode; 
                while(cur!=NULL){
                    if(!xmlStrcmp(cur->name,(const xmlChar*)"genre")){
                        genre_temp= (struct genre*)calloc(1,sizeof(struct genre));
                        
                        genre_temp=loadGenre(cur);
                        
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
    }
    general_layer.description.authors = author_head;
    general_layer.description.other_titles = other_title_head;
    general_layer.description.dates = date_head;
    general_layer.description.genres = genre_head;
}

void printDescription(){
    struct author *author_p=NULL;
    struct other_title *other_title_p=NULL;
    struct date* date_p=NULL;
    struct genre* genre_p=NULL;
    
    int i = 0;
    printf("\n#Description#\n");

    printf("Title: %s\n",general_layer.description.main_title);
    if(general_layer.description.number!=NULL) printf("Number: %s\n",general_layer.description.number);
    if(general_layer.description.work_title!=NULL) printf("Work Title: %s\n",general_layer.description.work_title);
    if(general_layer.description.work_number!=NULL) printf("Work Number: %s\n",general_layer.description.work_number);
    if(general_layer.description.authors!=NULL){
        author_p=general_layer.description.authors;
        printf("%i authors\n",general_layer.description.n_authors);
        i = 0;
        while(author_p!=NULL&&i<N_DISPLAY){
            i++;
            printf("name=%s: %s\n",author_p->type,author_p->name);
            author_p=author_p->next_author;
        }
        if (general_layer.description.n_authors > N_DISPLAY) printf("...\n");
    }
    if(general_layer.description.other_titles!=NULL){
        other_title_p=general_layer.description.other_titles;
        printf("%i other titles\n",general_layer.description.n_other_titles);
        i = 0;
        while(other_title_p!=NULL&&i< N_DISPLAY){
            i++;
            printf("Other title: %s\n",other_title_p->title_value);
            other_title_p=other_title_p->next_title;
        }
        if (general_layer.description.n_other_titles > N_DISPLAY) printf("...\n");
    }
    if(general_layer.description.dates!=NULL){
        date_p=general_layer.description.dates;
        printf("%i dates\n",general_layer.description.n_dates);
        i = 0;
        while(date_p!=NULL){
            i++;
            printf("Date: %s\n",date_p->date_value);
            date_p=date_p->next_date;
        }
        if (general_layer.description.n_dates > N_DISPLAY) printf("...\n");
    }
    if(general_layer.description.genres!=NULL){
        genre_p=general_layer.description.genres;
        printf("%i genres\n",general_layer.description.n_genres);
        i = 0;
        while(genre_p!=NULL){
            i++;
            printf("Genre: "); 
            if (genre_p->name) printf("name=%s ", genre_p->name);
            if (genre_p->description) printf("description=%s ", genre_p->description);
            if (genre_p->weight) printf("weight=%s ", genre_p->weight);
            printf("\n");
            genre_p=genre_p->next_genre;
        }
        if (general_layer.description.n_genres > N_DISPLAY) printf("...\n");
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
            if (!xmlStrcmp(cur->name, (const xmlChar*)"related_file")) {
                temp = (struct related_file*)calloc(1, sizeof(struct related_file));

                if(temp){
                attributes = cur->properties;
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                        temp->file_name = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_format")) {
                        temp->file_format = xmlGetProp(cur, attributes->name);

                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"encoding_format")) {
                        temp->encoding_format = xmlGetProp(cur, attributes->name);

                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        temp->description = xmlGetProp(cur, attributes->name);

                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"copyright")) {
                        temp->copyright = xmlGetProp(cur, attributes->name);

                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"notes")) {
                        temp->notes = xmlGetProp(cur, attributes->name);

                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_event_ref")) {
                        temp->start_event_ref = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_event_ref")) {
                        temp->end_event_ref = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }
                temp->next_file = NULL;
                if (head == NULL) {
                    head = temp;
                }
                else {
                    p = head;
                    while (p->next_file != NULL)
                        p = p->next_file;
                    p->next_file = temp;
                }
                general_layer.n_related_files++;
            }
                else { fprintf(stderr, "Memory allocation failed for 'related_file' element\n");  }
            }
        }
    }   
    general_layer.related_files = head;
}

void printRelatedFiles(){
    struct related_file* p=NULL;
    
    if (general_layer.n_related_files != 0) {

        int i = 0;
        printf("\n#Related Files#\n");

        printf("%i related files\n", general_layer.n_related_files);

        p = NULL;
        p = general_layer.related_files;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("File: ");
            if(p->file_name)
                printf("name=%s ",p->file_name);
            if (p->file_format)
                printf("format=%s ", p->file_format);
            if (p->encoding_format)
                printf("encoding=%s ", p->encoding_format);
            if (p->description)
                printf("description=%s ", p->description);
            if (p->copyright)
                printf("copyright=%s ", p->copyright);
            if (p->notes)
                printf("notes=%s ", p->notes);
            printf("\n");
            p = p->next_file;
        }
        if (general_layer.n_related_files > N_DISPLAY) printf("...\n");
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
                temp= (struct  analog_medium*)calloc(1,sizeof(struct analog_medium));

                if (temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                            temp->description = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"copyright")) {
                            temp->copyright = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"notes")) {
                            temp->notes = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }
                    temp->next_medium = NULL;
                    if (head == NULL) {
                        head = temp;
                    }
                    else {
                        p = head;
                        while (p->next_medium != NULL)
                            p = p->next_medium;
                        p->next_medium = temp;
                    }
                    general_layer.n_analog_media++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'analog_medium' element\n"); }
            }
        }
    }   
    general_layer.analog_media = head;
}

void printAnalogMedia(){
    struct analog_medium *p=NULL;

    if (general_layer.n_analog_media != 0) {
        int i = 0;
        printf("\n#Analog Media#\n");

        printf("%i analog media\n", general_layer.n_related_files);

        p = general_layer.analog_media;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("Medium: ");
            if(p->copyright)
                printf("copyright=%s",p->copyright);
            if (p->description)
                printf("description=%s", p->description);
            if (p->notes)
                printf("notes=%s", p->notes);
            printf("\n");
            p = p->next_medium;
        }
        if (general_layer.n_analog_media > N_DISPLAY) printf("...\n");
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
    if (general_layer.notes) {
        printf("\n#Notes#\n");
        printf("Notes: %s\n", general_layer.notes);
    }
}

void freeAuthorsList(struct author* head) {
    struct author* temp;
    while (head) {
        temp = head;
        head = head->next_author;
        free(temp);
    }
}

void freeOtherTitlesList(struct other_title* head) {
    struct other_title* temp;
    while (head) {
        temp = head;
        head = head->next_title;
        free(temp);
    }
}

void freeDatesList(struct date* head) {
    struct date* temp;
    while (head) {
        temp = head;
        head = head->next_date;
        free(temp);
    }
}

void freeRelatedFilesList(struct related_file* head) {
    struct related_file* temp;
    while (head) {
        temp = head;
        head = head->next_file;
        free(temp);
    }
}

void freeAnalogMediaList(struct analog_medium* head) {
    struct analog_medium* temp;
    while (head) {
        temp = head;
        head = head->next_medium;
        free(temp);
    }
}

void freeGeneralLayer(struct general cur) {
    if (cur.description.authors && cur.description.n_authors!=0)
        freeAuthorsList(cur.description.authors);
    if (cur.description.other_titles && cur.description.n_other_titles != 0)
        freeOtherTitlesList(cur.description.other_titles);
    if (cur.description.dates && cur.description.n_dates != 0)
        freeDatesList(cur.description.dates);
    if (cur.description.genres && cur.description.n_genres != 0)
        freeGenresList(cur.description.genres);

    if (cur.analog_media && cur.n_analog_media != 0)
        freeAnalogMediaList(cur.analog_media);

    if (cur.related_files && cur.n_related_files!=0)
        freeRelatedFilesList(cur.related_files);
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerAudio.h"

static struct audio audio_layer;

struct audio loadAudio(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct track* track_temp=NULL;
    struct track* track_head=NULL;
    struct track* track_p=NULL;
    audio_layer.n_tracks=0;
    
    xpath=(xmlChar *)"/ieee1599/audio/track";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning tracks 

            track_temp=(struct track*)malloc(sizeof(struct track));
            track_temp=calloc(1,sizeof(struct track));
            cur=nodeset->nodeTab[i];
            
            attributes=cur->properties;         
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_name")){
                    track_temp->file_name=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"file_format")){
                    track_temp->file_format=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"encoding_format")){
                    track_temp->encoding_format=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"md5")){
                    track_temp->md5=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }
            //load track elements           
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"track_general")){
                    track_temp->track_general=loadTrackGeneral(temp_cur);
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"track_indexing")){
                    track_temp->track_indexing=loadTrackIndexing(temp_cur);
                }
                else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"rights")){
                    track_temp->rights=loadRights(temp_cur);
                }
                temp_cur=temp_cur->next;
            }
            
            track_temp->next_track=NULL;
            if(track_head==NULL)
                track_head=track_temp;
            else{
                track_p=track_head;
                while(track_p->next_track!=NULL)
                    track_p=track_p->next_track;
                track_p->next_track=track_temp;
            }
            audio_layer.n_tracks++;
        }
        audio_layer.tracks=track_head;
    }
    
    return audio_layer;
}

struct track_general loadTrackGeneral(xmlNodePtr cur){
    struct track_general value;
    xmlAttr* attributes;
    xmlNodePtr temp_cur;

    struct recording* recording_temp=NULL;
    struct recording* recording_head=NULL;
    struct recording* recording_p=NULL;
    value.n_recordings=0;
    
    struct genre* genre_temp=NULL;
    struct genre* genre_head=NULL;
    struct genre* genre_p=NULL;
    value.n_genres=0;
    
    struct album* album_temp=NULL;
    struct album* album_head=NULL;
    struct album* album_p=NULL;
    value.n_albums=0;

    struct performer* performer_temp=NULL;
    struct performer* performer_head=NULL;
    struct performer* performer_p=NULL;
    value.n_performers=0;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"geographical_region")){
            value.geographical_region=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"lyrics_language")){
            value.lyrics_language =xmlGetProp(cur,attributes->name);   
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"recordings")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"recording")){
                    recording_temp=(struct recording*)malloc(sizeof(struct recording));
                    recording_temp=calloc(1,sizeof(struct recording));
                    
                    attributes=temp_cur->properties;
                    while(attributes!=NULL){
                        if(!xmlStrcmp(attributes->name,(const xmlChar*)"date")){
                            recording_temp->date=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"recorded_part")){
                            recording_temp->recorded_part=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"studio_name")){
                            recording_temp->studio_name=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"studio_address")){
                            recording_temp->studio_address=xmlGetProp(temp_cur,attributes->name);
                        }
                        attributes=attributes->next;
                    }
                    
                    recording_temp->next_recording=NULL;
                    if(recording_head==NULL)
                    recording_head=recording_temp;
                    else{
                        recording_p=recording_head;
                        while(recording_p->next_recording!=NULL)
                            recording_p=recording_p->next_recording;
                        recording_p->next_recording=recording_temp;
                    }
                    value.n_recordings++;
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"genres")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"genre")){
                    genre_temp=(struct genre*)malloc(sizeof(struct genre));
                    genre_temp=calloc(1,sizeof(struct genre));
                    
                    genre_temp=loadGenre(temp_cur);
                    
                    genre_temp->next_genre=NULL;
                    if(genre_head==NULL)
                    genre_head=genre_temp;
                    else{
                        genre_p=genre_head;
                        while(genre_p->next_genre!=NULL)
                            genre_p=genre_p->next_genre;
                        genre_p->next_genre=genre_temp;
                    }
                    value.n_genres++;
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"albums")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"album")){
                    album_temp=(struct album*)malloc(sizeof(struct album));
                    album_temp=calloc(1,sizeof(struct album));
                    
                    attributes=temp_cur->properties;
                    while(attributes!=NULL){
                        if(!xmlStrcmp(attributes->name,(const xmlChar*)"title")){
                            album_temp->title=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"track_number")){
                            album_temp->track_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"carrier_type")){
                            album_temp->carrier_type=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"catalogue_number")){
                            album_temp->catalogue_number=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"number_of_tracks")){
                            album_temp->number_of_tracks=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"publication_date")){
                            album_temp->publication_date=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"label")){
                            album_temp->label=xmlGetProp(temp_cur,attributes->name);
                        }
                        attributes=attributes->next;
                    }
                    
                    album_temp->next_album=NULL;
                    if(album_head==NULL)
                    album_head=album_temp;
                    else{
                        album_p=album_head;
                        while(album_p->next_album!=NULL)
                            album_p=album_p->next_album;
                        album_p->next_album=album_temp;
                    }
                    value.n_albums++;
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"performers")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"performer")){
                                        performer_temp=(struct performer*)malloc(sizeof(struct performer));
                    performer_temp=calloc(1,sizeof(struct performer));
                    
                    attributes=temp_cur->properties;
                    while(attributes!=NULL){
                        if(!xmlStrcmp(attributes->name,(const xmlChar*)"name")){
                            performer_temp->name=xmlGetProp(temp_cur,attributes->name);
                        }
                        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                            performer_temp->type=xmlGetProp(temp_cur,attributes->name);
                        }
                        attributes=attributes->next;
                    }
                    
                    performer_temp->next_performer=NULL;
                    if(performer_head==NULL)
                    performer_head=performer_temp;
                    else{
                        performer_p=performer_head;
                        while(performer_p->next_performer!=NULL)
                            performer_p=performer_p->next_performer;
                        performer_p->next_performer=performer_temp;
                    }
                    value.n_performers++;
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"notes")){
            value.notes=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }
        cur=cur->next;
    }
    value.recordings=recording_head;
    value.genres=genre_head;
    value.albums=album_head;
    value.performers=performer_head;
    
    return value;
}

struct track_indexing loadTrackIndexing(xmlNodePtr cur){
    struct track_indexing value;
    xmlAttr* attributes;

    struct track_region* track_region_temp=NULL;
    struct track_region* track_region_head=NULL;
    struct track_region* track_region_p=NULL;
    value.n_track_regions=0;
    
    struct track_event* track_event_temp=NULL;
    struct track_event* track_event_head=NULL;
    struct track_event* track_event_p=NULL;
    value.n_track_events=0;

    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"timing_type")){
            value.timing_type=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    cur=cur->xmlChildrenNode;
    while(cur!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"track_region")){
            track_region_temp=(struct track_region*)malloc(sizeof(struct track_region));
            track_region_temp=calloc(1,sizeof(struct track_region));

            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"name")){
                    track_region_temp->name=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    track_region_temp->description=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                    track_region_temp->start_event_ref=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                    track_region_temp->end_event_ref=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }

            track_region_temp->next_track_region=NULL;
            if(track_region_head==NULL)
            track_region_head=track_region_temp;
            else{
                track_region_p=track_region_head;
                while(track_region_p->next_track_region!=NULL)
                    track_region_p=track_region_p->next_track_region;
                track_region_p->next_track_region=track_region_temp;
            }
            value.n_track_regions++;
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"track_event")){
            track_event_temp=(struct track_event*)malloc(sizeof(struct track_event));
            track_event_temp=calloc(1,sizeof(struct track_event));

            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_time")){
                    track_event_temp->start_time=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_time")){
                    track_event_temp->end_time=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    track_event_temp->event_ref=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"description")){
                    track_event_temp->description=xmlGetProp(cur,attributes->name);
                }
                attributes=attributes->next;
            }

            track_event_temp->next_track_event=NULL;
            if(track_event_head==NULL)
            track_event_head=track_event_temp;
            else{
                track_event_p=track_event_head;
                while(track_event_p->next_track_event!=NULL)
                    track_event_p=track_event_p->next_track_event;
                track_event_p->next_track_event=track_event_temp;
            }
            value.n_track_events++; 
        }
        cur=cur->next;
    }
    value.track_regions=track_region_head;
    value.track_events=track_event_head;
    
    return value;
}

void printAudio(){
    if(audio_layer.n_tracks!=0){
        printf("There are %i tracks\n",audio_layer.n_tracks);
        //printf(audio_layer.tracks)
        struct track* temp=audio_layer.tracks;
        while(temp!=NULL){
            printf("%s ",temp->file_name);
            printTrackGeneral(temp->track_general);
            printTrackIndexing(temp->track_indexing);
            temp=temp->next_track;
            printf("\n");
        }
    }
}

void printTrackGeneral(struct track_general cur){
    
}

void printTrackIndexing(struct track_indexing cur){

}
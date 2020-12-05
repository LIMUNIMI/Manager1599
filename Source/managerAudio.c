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

            track_temp=(struct track*)calloc(1,sizeof(struct track));
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

    value.notes = NULL;
    value.geographical_region = NULL;
    value.lyrics_language = NULL;

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
                    recording_temp=(struct recording*)calloc(1,sizeof(struct recording));
                    
                    if (recording_temp) {
                        attributes = temp_cur->properties;
                        while (attributes != NULL) {
                            if (!xmlStrcmp(attributes->name, (const xmlChar*)"date")) {
                                recording_temp->date = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"recorded_part")) {
                                recording_temp->recorded_part = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"studio_name")) {
                                recording_temp->studio_name = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"studio_address")) {
                                recording_temp->studio_address = xmlGetProp(temp_cur, attributes->name);
                            }
                            attributes = attributes->next;
                        }

                        recording_temp->next_recording = NULL;
                        if (recording_head == NULL)
                            recording_head = recording_temp;
                        else {
                            recording_p = recording_head;
                            while (recording_p->next_recording != NULL)
                                recording_p = recording_p->next_recording;
                            recording_p->next_recording = recording_temp;
                        }
                        value.n_recordings++;
                    }
                    else { fprintf(stderr, "Memory allocation failed for 'recording' element\n");  }
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"genres")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"genre")){
                    genre_temp=(struct genre*)calloc(1,sizeof(struct genre));
                    
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
                    album_temp=(struct album*)calloc(1,sizeof(struct album));
                    
                    if (album_temp) {
                        attributes = temp_cur->properties;
                        while (attributes != NULL) {
                            if (!xmlStrcmp(attributes->name, (const xmlChar*)"title")) {
                                album_temp->title = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"track_number")) {
                                album_temp->track_number = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"carrier_type")) {
                                album_temp->carrier_type = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"catalogue_number")) {
                                album_temp->catalogue_number = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"number_of_tracks")) {
                                album_temp->number_of_tracks = xmlCharToInt(xmlGetProp(temp_cur, attributes->name));
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"publication_date")) {
                                album_temp->publication_date = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"label")) {
                                album_temp->label = xmlGetProp(temp_cur, attributes->name);
                            }
                            attributes = attributes->next;
                        }

                        album_temp->next_album = NULL;
                        if (album_head == NULL)
                            album_head = album_temp;
                        else {
                            album_p = album_head;
                            while (album_p->next_album != NULL)
                                album_p = album_p->next_album;
                            album_p->next_album = album_temp;
                        }
                        value.n_albums++;
                    }
                    else { fprintf(stderr, "Memory allocation failed for 'album' element\n"); }
                }
                temp_cur=temp_cur->next;
            }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"performers")){
            temp_cur=cur->xmlChildrenNode;
            while(temp_cur!=NULL){
                if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"performer")){
                    performer_temp=(struct performer*)calloc(1,sizeof(struct performer));
                    
                    if (performer_temp) {
                        attributes = temp_cur->properties;
                        while (attributes != NULL) {
                            if (!xmlStrcmp(attributes->name, (const xmlChar*)"name")) {
                                performer_temp->name = xmlGetProp(temp_cur, attributes->name);
                            }
                            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"type")) {
                                performer_temp->type = xmlGetProp(temp_cur, attributes->name);
                            }
                            attributes = attributes->next;
                        }

                        performer_temp->next_performer = NULL;
                        if (performer_head == NULL)
                            performer_head = performer_temp;
                        else {
                            performer_p = performer_head;
                            while (performer_p->next_performer != NULL)
                                performer_p = performer_p->next_performer;
                            performer_p->next_performer = performer_temp;
                        }
                        value.n_performers++;
                    }
                    else { fprintf(stderr, "Memory allocation failed for 'performer' element\n");  }
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

    value.timing_type = NULL;

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
            track_region_temp=(struct track_region*)calloc(1,sizeof(struct track_region));

            if (track_region_temp) {
                attributes = cur->properties;
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"name")) {
                        track_region_temp->name = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        track_region_temp->description = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_event_ref")) {
                        track_region_temp->start_event_ref = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_event_ref")) {
                        track_region_temp->end_event_ref = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }


                track_region_temp->next_track_region = NULL;
                if (track_region_head == NULL)
                    track_region_head = track_region_temp;
                else {
                    track_region_p = track_region_head;
                    while (track_region_p->next_track_region != NULL)
                        track_region_p = track_region_p->next_track_region;
                    track_region_p->next_track_region = track_region_temp;
                }
                value.n_track_regions++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'track_region' element\n");  }
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"track_event")){
            track_event_temp=(struct track_event*)calloc(1,sizeof(struct track_event));

            if (track_event_temp) {
                attributes = cur->properties;
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_time")) {
                        track_event_temp->start_time = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_time")) {
                        track_event_temp->end_time = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                        track_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                    }
                    else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        track_event_temp->description = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }

                track_event_temp->next_track_event = NULL;
                if (track_event_head == NULL)
                    track_event_head = track_event_temp;
                else {
                    track_event_p = track_event_head;
                    while (track_event_p->next_track_event != NULL)
                        track_event_p = track_event_p->next_track_event;
                    track_event_p->next_track_event = track_event_temp;
                }
                value.n_track_events++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'track_event' element\n");  }
        }
        cur=cur->next;
    }
    value.track_regions=track_region_head;
    value.track_events=track_event_head;
    
    return value;
}

void printAudio(){
    if(audio_layer.n_tracks!=0){
        int i = 0;
        printf("\n###Audio Layer###\n");

        printf("%i tracks\n",audio_layer.n_tracks);

        i = 0;
        struct track* p=audio_layer.tracks;
        while(p!=NULL&&i<N_DISPLAY){
            i++;
            printf("%s\n",p->file_name);
            printTrackGeneral(p->track_general);
            printTrackIndexing(p->track_indexing);
            if (p->rights.file_name)
                printf("(%s)",p->rights.file_name);
            p=p->next_track;
            printf("\n");
        }
        if (audio_layer.n_tracks > N_DISPLAY) printf("...\n");
    }
}

void printTrackGeneral(struct track_general cur){
    
    int i = 0;
    printf("    Track General ");
    if (cur.geographical_region || cur.lyrics_language) {
        printf("( ");
        if (cur.geographical_region) printf("region=%s ",cur.geographical_region);
        if (cur.lyrics_language) printf("language=%s ", cur.lyrics_language);
        printf(" )");
    }
    printf("\n");

    if (cur.n_recordings != 0) {
        printf("    -Recordings: ");
        struct recording* p = cur.recordings;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if(p->date)
                printf("date=%s ",cur.recordings->date);
            if (p->recorded_part)
                printf("recorded part=%s ", p->recorded_part);
            if (p->studio_name)
                printf("studio=%s ",p->studio_name);
            if (p->studio_address)
                printf("address=%s ", p->studio_address);
            printf(" ) ");
            p = p->next_recording;
        }
        if (cur.n_recordings > N_DISPLAY) printf("...");
        printf("\n");
    }

    if (cur.n_genres != 0) {
        printf("    -Genres: ");
        struct genre* p = cur.genres;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->name)
                printf("name=%s ", p->name);
            if (p->description)
                printf("description=%s ", p->description);
            if (p->weight)
                printf("weight=%s ", p->weight);
            printf(" ) ");
            p = p->next_genre;
        }
        if (cur.n_genres > N_DISPLAY) printf("...");
        printf("\n");
    }

    if (cur.n_albums != 0) {
        printf("    -Albums: ");
        struct album* p = cur.albums;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->title)
                printf("title=%s ", p->title);
            if (p->track_number)
                printf("track=%i ", p->track_number);
            if (p->carrier_type)
                printf("carrier=%s ", p->carrier_type);
            if (p->catalogue_number)
                printf("catalog number=%s ", p->catalogue_number);
            if (p->number_of_tracks)
                printf("tracks=%i ", p->number_of_tracks);
            if (p->publication_date)
                printf("pubblication=%s ", p->publication_date);
            if (p->label)
                printf("label=%s ", p->label);
            printf(" ) ");
            p = p->next_album;
        }
        if (cur.n_albums > N_DISPLAY) printf("...");
        printf("\n");
    }

    if (cur.n_performers != 0) {
        printf("    -Performers: ");
        struct performer* p = cur.performers;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->name)
                printf("name=%s ", p->name);
            if (p->type)
                printf("type=%s ", p->type);
            printf(" ) ");
            p = p->next_performer;
        }
        if (cur.n_performers > N_DISPLAY) printf("...");
        printf("\n");
    }

    if (cur.notes) {
        printf("    -%s\n",cur.notes);
    }
}

void printTrackIndexing(struct track_indexing cur){
    int i = 0;
    printf("    Track Indexing ");
    if (cur.timing_type) printf("( %s )", cur.timing_type);
    printf("\n");

    if (cur.n_track_regions != 0) {
        printf("    -Track Regions: ");
        struct track_region* p = cur.track_regions;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->name)
                printf("name=%s ", p->name);
            if (p->description)
                printf("description=%s ", p->description);
            if (p->start_event_ref)
                printf("start event ref=%s ", p->start_event_ref);
            if (p->end_event_ref)
                printf("end event ref=%s ", p->end_event_ref);
            printf(" ) ");
            p = p->next_track_region;
        }
        if (cur.n_track_regions > N_DISPLAY) printf("...");
        printf("\n");
    }

    if (cur.n_track_events != 0) {
        printf("    -Track Events: ");
        struct track_event* p = cur.track_events;
        i = 0;
        while (p != NULL && i < N_DISPLAY) {
            i++;
            printf("( ");
            if (p->start_time)
                printf("start time=%s ", p->start_time);
            if (p->end_time)
                printf("end time=%s ", p->end_time);
            if (p->event_ref)
                printf("event ref=%s ", p->event_ref);
            if (p->description)
                printf("description%s ", p->description);
            printf(" ) ");
            p = p->next_track_event;
        }
        if (cur.n_track_events > N_DISPLAY) printf("...");
        printf("\n");
    }

}
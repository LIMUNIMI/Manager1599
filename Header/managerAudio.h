/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   managerAudio.h
 * Author: Ale
 *
 * Created on 5 settembre 2020, 17.36
 */

#ifndef MANAGERAUDIO_H
#define MANAGERAUDIO_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "common.h"

//Track General
    struct recording{
        xmlChar* date;//REQUIRED
        xmlChar* recorded_part;
        xmlChar* studio_name;
        xmlChar* studio_address;

        struct recording* next_recording;
    };
    
    struct album{
        xmlChar* title;//REQUIRED
        int track_number;//REQUIRED
        xmlChar* carrier_type;
        xmlChar* catalogue_number;
        int number_of_tracks;
        xmlChar* publication_date;
        xmlChar* label;

        struct album* next_album;
    };
    
    struct performer{
        xmlChar* name;//REQUIRED
        xmlChar* type;//REQUIRED
        
        struct performer* next_performer;
    };
    
    struct track_general{//(recordings?, genres?, albums?, performers?, notes?)
        int n_recordings;
        int n_genres;
        int n_albums;
        int n_performers;
        
        xmlChar* geographical_region;
        xmlChar* lyrics_language;
        
        struct recording* recordings;
        struct genre* genres;
        struct album* albums;
        struct performer* performers;
        xmlChar* notes;
    };
//Track Indexing
    struct track_event{
        xmlChar* start_time;//REQUIRED
	    xmlChar* end_time;
        xmlChar* event_ref;
 	    xmlChar* description;
        
        struct track_event* next_track_event;
    };
    
    struct track_region{
        xmlChar* name;//REQUIRED
        xmlChar* description;
        xmlChar* start_event_ref;
        xmlChar* end_event_ref;
        
        struct track_region* next_track_region;
    };
    
    struct track_indexing{//(track_region*, track_event+)
        int n_track_regions;
        int n_track_events;
        
        xmlChar* timing_type;//REQUIRED
        
        struct track_region* track_regions;
        struct track_event* track_events;
    };
//Audio
    struct track{//(track_general?, track_indexing?, rights?)
        xmlChar* file_name;//REQUIRED
        xmlChar* file_format;//REQUIRED
        xmlChar* encoding_format;//REQUIRED
        xmlChar* md5;
        
        struct track_general track_general;
        struct track_indexing track_indexing;
        struct rights rights;
        
        struct track* next_track;
    };
    
    struct audio{
        int n_tracks;
        
        struct track* tracks;
    };

//Variables

    
//Prototypes
    MANAGERIEEE1599_API struct audio loadAudio();
    struct track_general loadTrackGeneral(xmlNodePtr cur);
    struct track_indexing loadTrackIndexing(xmlNodePtr cur);    
    
    MANAGERIEEE1599_API void printAudio();
    MANAGERIEEE1599_API void printTrackGeneral(struct track_general cur);
    MANAGERIEEE1599_API void printTrackIndexing(struct track_indexing cur);

#ifdef __cplusplus
}
#endif

#endif /* MANAGERAUDIO_H */


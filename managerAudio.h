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
        char* date;//REQUIRED
        char* recorded_part;
        char* studio_name;
        char* studio_address;

        struct recording* next_recording;
    };
    
    struct album{
        char* title;//REQUIRED
        int track_number;//REQUIRED
        char* carrier_type;
        char* catalogue_number;
        int number_of_tracks;
        char* publication_date;
        char* label;

        struct album* next_album;
    };
    
    struct performer{
        char* name;//REQUIRED
        char* type;//REQUIRED
        
        struct performer* next_performer;
    };
    
    struct track_general{//(recordings?, genres?, albums?, performers?, notes?)
        int n_recordings;
        int n_genres;
        int n_albums;
        int n_performers;
        
        char* geographical_region;
        char* lyrics_language;
        
        struct recording* recordings;
        struct genre* genres;
        struct album* albums;
        struct performer* performers;
        char* notes;
    };
//Track Indexing
    struct track_event{
        char* start_time;//REQUIRED
	char* end_time;
        //spine_ref;
 	char* description;
        
        struct track_event* next_track_event;
    };
    
    struct track_region{
        char* name;//REQUIRED
        char* description;
        //spine_start_end_ref
        
        struct track_region* next_track_region;
    };
    
    struct track_indexing{//(track_region*, track_event+)
        int n_track_regions;
        int n_track_events;
        
        char* timing_type;//REQUIRED
        
        struct track_region* track_regions;
        struct track_event* track_events;
    };
//Audio
    struct track{//(track_general?, track_indexing?, rights?)
        char* file_name;//REQUIRED
        char* file_format;//REQUIRED
        char* encoding_format;//REQUIRED
        char* md5;
        
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
    struct audio audio_layer;
    
//Prototypes
    void loadAudio();
    struct track_general loadTrackGeneral(xmlNodePtr cur);
    struct track_indexing loadTrackIndexing(xmlNodePtr cur);    
    
    void printAudio();
    void printTrackGeneral(struct track_general cur);
    void printTrackIndexing(struct track_indexing cur);

#ifdef __cplusplus
}
#endif

#endif /* MANAGERAUDIO_H */


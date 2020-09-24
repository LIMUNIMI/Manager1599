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
    struct recording{};
    
    struct album{};
    
    struct performer{};
    
    struct track_general{//(recordings?, genres?, albums?, performers?, notes?)
        char* geographical_region;
        char* lyrics_language;
        
        struct recording* recorings;
        struct genre* genres;
        struct album* albums;
        struct performer* performers;
        char* notes;
    };
//Track Indexing
    struct track_indexing{//(track_region*, track_event+)
    
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
    
    void printAudio();

#ifdef __cplusplus
}
#endif

#endif /* MANAGERAUDIO_H */


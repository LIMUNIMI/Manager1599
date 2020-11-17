/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   fileChooser.h
 * Author: Ale
 *
 * Created on 4 ottobre 2020, 6.52
 */

#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "common.h"
    #include <dirent.h>
    #include <sys/stat.h>

    extern char* rootFolderPath;
    
    void setRootFolderPath(char* path);
    char* getRootFolderPath();
    char* chooseFile();
    int showFiles();
    char* readFileName(int choice);
    const char* getExtension(const char *file_name);
    
#ifdef __cplusplus
}
#endif

#endif /* FILECHOOSER_H */


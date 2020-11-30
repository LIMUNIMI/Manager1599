/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   fileChooser.h
 * Author: Alessandro Talamona
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

    MANAGERIEEE1599_API char* chooseFile();
    MANAGERIEEE1599_API int showFiles();
    MANAGERIEEE1599_API const char* getExtension(const char *file_name);
    char* readFileName(int choice);

#ifdef __cplusplus
}
#endif

#endif /* FILECHOOSER_H */


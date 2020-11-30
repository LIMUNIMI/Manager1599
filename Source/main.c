/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Alessandro Talamona
 *
 * Created on 28 luglio 2020, 23.09
 */

#include "managerDocument.h"
#include "fileChooser.h"

int main(int argc, char **argv) {
     
    int confirm = 1;

    while (confirm == 1) {
        setFileName(chooseFile());
        if (strcmp(getFileName(), (const char*)"")) {
            if (getDoc((xmlChar*)(getFileName())) == 1) {
                fprintf(stdout, "Loaded %s\n", getFileName());
                loadDocument();
                printDocument();
            }

            do { 
                printf("\nContinue? [yes=1,No=0]\n"); 
            }
            while(!scanf("%i", &confirm));

            clean();
        }
        else confirm = 0;
    }
            
    return (EXIT_SUCCESS);
}
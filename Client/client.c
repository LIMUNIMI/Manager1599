#include "managerDocument.h"
#include "fileChooser.h"

void main() {

    int confirm = 1;
    int force_validation = 0;

    while (confirm == 1) {
        clean();
        setFileName(chooseFile());
        if (strcmp((const char*)getFileName(), (const char*)"")) {
            if (getDoc((xmlChar*)getFileName(),force_validation) == 1) {
                fprintf(stdout, "Loaded %s\n", getFileName());
                loadDocument();
                printDocument();
                freeDocument();
            }

            do {
                printf("\nContinue? [yes=1,No=0]\n");
            } while (!scanf("%i", &confirm));
        }
        else confirm = 0;
    }
}
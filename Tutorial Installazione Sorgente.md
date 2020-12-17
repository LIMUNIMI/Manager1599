## Istruzioni per l'installazione

1. Installare la libreria **dirent** per utilizzare le funzioni in * *fileChooser.h* *
2. Installare la libreria **libxml2** (che richiede le librerie **zib1** e **iconv**).
3. Posizionare la cartella * *File* * (che contiene la cartella * *DTD* *) nella root directory del progetto.
     - È possibile rimuovere ed aggiungere i file XML. Non rimuovere i file DTD.
4. Posizionare i file delle cartelle * *Source* * e * *Header* * nella root directory del progetto.

### Installazione Per Visual Studio

1. Installare **dirent** con **NuGet**.
2. Scaricare le cartelle * *Libraries* * e * *DLL* *. Spostare il contenuto della seconda cartella nella root direcotry del progetto, insieme ai file sorgente.
     - Libraries contiene le librerie **libxml2**, **iconv** e **zlib1**. I file nella cartella * *DLL* * sono gli stessi contenuti nelle loro cartelle * *bin* *.
3. Scaricare la cartella * *File* e spostarla nella root directory del progetto, insieme ai file sorgente.
4. Scaricare le cartelle * *Source* * e * *Header* * e posizionare i file al loro interno nella root directory del progetto.

Nelle Proprietá di configurazone del progetto:
1. In `C/C++ > Generale > Directory di inclusione aggiuntive` aggiungere il percorso alla cartella * *include* * (compresa) delle librerie **libxml2** e **iconv**.
2. In `C/C++ > Riga di comando > Opzioni aggiuntive` inserie il comando * */wd4996* *.
3. In `Linker > Generale > Directory librerie aggiuntive` aggiungere il percorso alla cartella * *lib* * (compresa) delle librerie **libxml2** e **iconv**.
4. In `Linker > Input > Dipendenza aggiuntive` aggiungere * *libxml2.lib* * e * *iconv.lib* *.

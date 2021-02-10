## Istruzioni per l'installazione

1. Installare la libreria **dirent** per utilizzare le funzioni in _fileChooser.h_
2. Installare la libreria **libxml2** (che richiede le librerie **zib1** e **iconv**).
3. Posizionare la cartella _File_ (che contiene la cartella _DTD_) nella root directory del progetto.
     - È possibile rimuovere ed aggiungere i file XML. Non rimuovere i file DTD.
4. Posizionare i file delle cartelle _Source_ e _Header_ nella root directory del progetto.

### Installazione Per Visual Studio

1. Installare **dirent** con **NuGet**.
2. Scaricare le cartelle _Libraries_ e _DLL_. Spostare il contenuto della seconda cartella nella root direcotry del progetto, insieme ai file sorgente.
     - Libraries contiene le librerie **libxml2**, **iconv** e **zlib1**. I file nella cartella _DLL_ sono gli stessi contenuti nelle loro cartelle _bin_.
3. Scaricare la cartella _File_ e spostarla nella root directory del progetto, insieme ai file sorgente.
4. Scaricare le cartelle _Source_ e _Header_ e posizionare i file al loro interno nella root directory del progetto.

Nelle Proprietá di configurazone del progetto:
1. In `C/C++ > Generale > Directory di inclusione aggiuntive` aggiungere il percorso alla cartella _include_ (compresa) delle librerie **libxml2** e **iconv**.
2. In `C/C++ > Riga di comando > Opzioni aggiuntive` inserie il comando _/wd4996_.
3. In `Linker > Generale > Directory librerie aggiuntive` aggiungere il percorso alla cartella _lib_ (compresa) delle librerie **libxml2** e **iconv**.
4. In `Linker > Input > Dipendenza aggiuntive` aggiungere _libxml2.lib_ e _iconv.lib_.

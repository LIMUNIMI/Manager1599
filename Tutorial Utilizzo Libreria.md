## Utilizzare la libreria

Per importare e utilizzare la libreria in programmi esterni, sono necessari i file di intestazione, i file _.lib_ e i file  _.dll_.

Nelle Proprietá di configurazone del progetto:
1. In `C/C++ > Generale > Directory di inclusione aggiuntive` aggiungere il percorso alla cartella _include_ (compresa) delle librerie **libxml2**,**iconv** e "managerieee1599".
2. In `C/C++ > Riga di comando > Opzioni aggiuntive` inserie il comando _/wd4996_.
3. In `Linker > Generale > Directory librerie aggiuntive` aggiungere il percorso alla cartella _lib_ (compresa) delle librerie **libxml2** e **iconv** e "managerieee1599".
4. In `Linker > Input > Dipendenza aggiuntive` aggiungere _libxml2.lib_,_iconv.lib_ e "managerieee1599.lib".
5. Copiare e incollare i file _.dll_ dalle cartelle _bin_ delle librerie alla directory di lavoro del programma che le utilizza.

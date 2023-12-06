# ToDo's

## Garbage Collecten
* Gesamtes Projekt von anfang bis ende durchgehen und alle nicht notwendigen/Überflüsigen Zeilen code löschen

## Songs Abspielen
* Beim hinzufügen eines Songs die möglichkeit geben den Pfad zu einer dazugehörigen mp3 oder mp4 Datei anzugeben und einen Eigenen menüpunkt hinzufügen um Songs abzuspielen die eine mp3 oder mp4 datei hinterlegt haben,
diese sollen einfach im Windows MediaPlayer bzw mit der Standart Anwendung für mp3 / mp4 Datein abgespielt werden.
  * Nur jene Songs auflisten die auch eine mp3 / mp4 datei hinterlegt haben
* Man soll den Pfad (relativ oder absolut) zur mp3 / mp4 datei eingeben nachdem man ausgewählt hat ob es sich um eine mp3 oder mp4 datei handelt, diese datei soll anschließend (mit z.B. dem system() befehl) in einen 
Vordefinierten ordner kopiert und umbenannt werden in dem sich alle mp3 / mp4 datein befinden __(Evtl. Auch per Explorer Fenster datei auswählen lassen fals das in C Funktioniert)__
* Man soll einzelne mp3 / mp4 Dateien auch wieder löschen können sodass kein Song mehr zu diesen hinterlegt ist

## UserData Speicher
* Bei jedem ausführen eine "Userdata" datei laden in der der Pfad zur Song Liste und zum Music Ordner drinnen stehen
* Diese Pfade soll man dann in einem extra Menüpunkt ändern können, sollte die erste Zeile leer sein so soll zu start gebeten werden den Pfad zur SongList anzugeben bzw. diese per explorer zu öffnen,
sollte die zweite Zeile leer sein, so soll zu start gebeten werden den Pfad zum Music Ordner anzugeben bzw diesen im Explorer auszuwählen.
* Evtl. Anzahl der in der Liste vorhandenen Songs in der 3ten zeile speichern und falls diese leer sein sollte wird die funktion setIndexCount aufgerufen, nach jedem hinzufügen/entfernen/jeder Informations Änderung
soll der aktualisierte IndexCount sofort wieder in die Datei geschrieben werden.
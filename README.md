classi per movimento di un personaggio in un gioco 2D, implementazione grafica tramite sfml.
repository creata tramite la funzione template di github.
la ricerca del percorso avviene tramite algoritmo A* (STL A* Search implementation (C)2001 Justin Heyes-Jones), il 
codice ci quest'implementazione è solo stato modificato per poter funzionare sul programma e sono stati aggiunti due 
metodi statici, usati per il corretto passaggio della mappa e per evidenziare il percorso trovato.
Le caselle percorribili sono colorate con sfumature di verde, assegnate a seconda del costo di percorrenza:
verde chiaro -> costo 1, verde scuro -> costo 5. Il costo determina la velocità di percorrenza della casella: 
velocità = 5 / costo_casella.


test eseguiti: 
    -   personaggio:
            - posizione iniziale;
            - movimnento (da casella (0,0) a casella (1,1), 120 passaggi, 60 sulla x e 60 sulla y, + altri 10 per
                controllorare che non si sposti ulteriormente);
    -   ricerca percorso: 
            - ricerca percorso da casella valida a valida con successo;
            - ricerca percorso da casella valida a casella non valida fallisce;
            - controllo su eventuali memory leak;

#include <iostream>
#include <time.h>
#include <chrono>

using namespace std :: chrono;
using namespace std;


int main () {

    int num_facce;
    long num_lanci;
    int dado1, dado2;
    int somma;


    
    cout << "Hai a disposizione 2 dadi. Puoi scegliere la tipologia tra quelli proposti sotto\n";
    cout << "Sto supponendo che tutte le facce dei dadi abbiano la stessa probabilita di comparire\n";
    cout << "\ttetraedro: 4 facce\n" <<
            "\tcubo: 6 facce\n" << "\tottaedro: 8 facce\n" << "\tdoedecaedro: 12 facce\n";
    
    cout << "Quante facce?\n";
    cin >> num_facce; 

    //controllo sul numero di facce
    //creiamo una lista (array) dei valori possibili

    int lista [] = {4,6,8,12};
    int elementi = sizeof(lista)/4;    //perchè 4 sono i byte occupati da un intero

    int flag=0;
    for (int i=0; i<elementi; i++) {
        if (num_facce==lista[i]) {
            flag=1;
        }
    }

    if (flag==0) {
        cout << "Dado non disponibile! Riprova\n";
        return 0;
    }

    /*if ((num_facce != 4) || (num_facce != 6) || (num_facce!=8) || (num_facce != 12)) {

        cout << "Dado non disponibile! Riprova\n";
        return 0;
    }
    */

    cout << "Quante volte vuoi tirare?\n";
    cin >> num_lanci;


    
    //AVVIO PROFILING DEL CODICE
    auto start = high_resolution_clock::now();

    
    
    int*array_somme_ottenute= new int [num_lanci];  //inizializzazione di un array dinamico per contenere la somma di ogni lancio

    srand (time(NULL));   //piazziamo il seme per generare i random
    long tiri_effettuati=0;
    
    //riempiamo l'array delle somme
    
    long l=0; //ci servirà per posizionare le somme nell'array
    while (tiri_effettuati<num_lanci) {
        
        dado1= rand() % num_facce+1;      //lancio dei dadi
        dado2= rand() % num_facce+1;
        tiri_effettuati+=1;             //conteggio dei tiri effettuati
        somma = dado1+dado2;            //calcolo della somma delle facce
        array_somme_ottenute[l] = somma;         //posizionamento delle somme nell'array
        l++;
    }

    int num_somme_possibili= (num_facce*2)-1;

    
    
    // NON SAREBBE MEGLIO UNA MATRICE INVECE CHE ALTRI 2 ARRAY? MA COME SI FA?
    int*array_possibili_somme= new int [num_somme_possibili];

    //creazione di un array contente tutte le possibili somme ottenibili
    for (int i=2; i<=num_somme_possibili+1; ++i) {
        
        array_possibili_somme[i-2] = i;
    }

    
    //conteggio di quante volte ogni possibile somma è stata ottenuta
    //senza la matrice tocca fare un altro array

    long* array_contaripetizioni = new long (num_somme_possibili);

    //mettiamo a zero tutti gli elementi dell'array in cui avremo il conteggio delle ripetizioni delle somme
    for (int i=0; i<num_somme_possibili; ++i) {
        
        array_contaripetizioni[i] = 0;
    }
    
    
    //contiamo quante volte ogni possibile somma compare nell'array delle somme, e segnamo nell'array contaripetizioni
    
    int j;
    for (int i=0; i<num_somme_possibili; ++i) {
        
        j=0;
        while (j<num_lanci) {

            if(array_possibili_somme[i] == array_somme_ottenute [j]) {

                array_contaripetizioni[i] += 1;
            }

            j++;
        }
    }

    
    //STOP PROFILING DEL CODICE
    auto stop = high_resolution_clock::now();
    //CALCOLO DEL TEMPO DI ESECUZIONE
    auto duration = duration_cast<microseconds>(stop-start);


    //utilizziamo un loop per mandare in output i risultati
    
    float probabilita=0;
    for (int i=0; i<num_somme_possibili; i++) {

        probabilita = ((float) array_contaripetizioni[i]/(float) num_lanci);

        cout << i+1 << "^ somma possibile:  " << array_possibili_somme[i] <<  " --->\t";                                                  
        cout << "Distribuzione di probabilita: " <<  probabilita << endl << endl;
    }

    cout << "L'esecuzione è stata di " << duration.count() << endl;

    
    delete [] array_somme_ottenute;
    delete [] array_possibili_somme;
    delete [] array_contaripetizioni;
    

    /*cout << endl << endl << "Premi 1 per riprovare. Premi un qualsiasi altro numero per uscire\n";
    cin >> scelta;

    }

    while (scelta==1);
    */
    
    return 0;

}
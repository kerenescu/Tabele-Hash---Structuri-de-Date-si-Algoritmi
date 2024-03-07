#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tlg.h"
#include "tabHash.h"

#define MAX 256

// operatii
// - construire tabela hash (+ definire functia de hash)
// - inserare element (si trebuie pastrata ordonarea impusa la nodurile din liste si subliste)
//   - aici cred ca este nevoie sa modificam TLG-ul, ca sa primeasca si o functie de comparare la inserare (pe baza careia sa puna elementul nou de inserat)
//   - de asemenea, ar trebui sa poata sa primeasca o functie care sa determine ce sa faca atunci cand se repeta unele valori / sa returneze o valoare 
//     speciala cand incercam sa adaugam acelasi element de mai multe ori in lista
// - printare elemente (si aici trebuie putin modificat TLG-ul pentru ca tema are cerinte putin diferite de printare, dar nu cred ca sunt modificari prea mari)
//   - de asemenea, mai avem printarile specifice (doar cuvintele cu o anumita lungime, etc); pentru astea as implementa niste functii de cautare in interiorul
//     tlg-ului / thash-ului sau implementat direct in main

// functii
// - functia hash
// - creare tabela hash
// - inserare cuvant (cred?)

int functieHash(void *element)
{
    char *cuvant = (char*) element;
    char initiala = tolower(cuvant[0]);
    return initiala - 'a';
}

TH *GenerareHash()
{
    TH *h = NULL;
    size_t M = 'z' - 'a' + 1;

    // initializare tabela hash
    h = (TH *) InitTH(M, functieHash);

    // daca a aparut vreo eroare
    if (h == NULL) {
        return NULL;
    }

    return h;
}



// int main(int argc, char *argv)
// FILEf = fopen(argv[1], "r");

int main(int argc, char **argv)
{
    // deschidere fisier
    FILE *fin = stdin;    
    if (argc >= 2 && argv[1] != NULL) {
        fin = fopen(argv[1], "r");
    }

    // creare tabela hash
    TH *h = GenerareHash();
    if (h == NULL) {
        printf("Eroare alocare tabela hash!\n");
        return 0;
    }

    char s[MAX] = "";
    char delims[] = " ,.\n";
    while (fgets(s, MAX, fin) != NULL) {
        char *p = strtok(s, delims);

        // selectie comanda
        if (strcmp(p, "insert") == 0) {
            p = strtok(NULL, delims);
            for (; p != NULL; p = strtok(NULL, delims)) {
                if (strlen(p) < 3) {
                    continue;
                }

                if (InsTH(h, p) == 0) {
                    printf("Eroare la inserare!\n");
                    break;
                }
            }
        }

        else if (strcmp(p, "print") == 0) {
            p = strtok(NULL, delims);
            if (p == NULL) {
                AfiTH(h);
            } else if ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z')) {
                char c = p[0];
                p = strtok(NULL, delims);
                int n = atoi(p);
                AfiTH_litera_lungime(h, c, n);
            } else {
                int n = atoi(p);
                AfiTH_aparitii_max(h, n);
            }
        }
        else if (strcmp(s, "exit") == 0) {
            break;
        }

    }

    // eliberare tabela hash
    DistrTH(&h);
    return 0;
}
/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
int Ins_DupaLG(TLG, void*); /*- inserare dupa un element -*/
int Ins_OrdLG(TLG*, TFCmp, void*); /*- inserare element, pastrand ordinea -*/
int Del_IncLG(TLG*, TF); /*- stergere primul element -*/
int Del_DupaLG(TLG, TF); /*- stergere dupa un element -*/
int Del_Elem(TLG*, TF, TFCmp, void*); /*- stergere element in functie de continut -*/
void* CautareLG(TLG, TFCmp, void*); /*- cautare element in lista ordonata -*/
void DistrugeLG(TLG* aL, TF fe); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*, TF, const char*);

#endif

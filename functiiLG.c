/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

int Ins_IncLG(TLG* aL, void* ae)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;

	return 1;
}

int Ins_DupaLG(TLG aL, void* ae)
{
	if(aL == NULL)
		return 0;

	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;

	aux->info = ae;
	aux->urm = aL->urm;
	aL->urm = aux;

	return 1;
}

int Ins_OrdLG(TLG *aL, TFCmp fcmp, void* elem)
{
	if (*aL == NULL || fcmp(elem, (*aL)->info) < 0) {
		return Ins_IncLG(aL, elem);
	}

	TLG el = *aL;
	while (el != NULL) {
		if (el->urm == NULL || fcmp (elem, el->urm->info) < 0) {
			return Ins_DupaLG(el, elem);
		}
		el = el->urm;
	}

	return 0;
}

int Del_IncLG(TLG *aL, TF free_elem)
{
	if(*aL == NULL)
		return 0;

	TLG del = *aL;
	*aL = del->urm;

	free_elem(del->info);
	free(del);

	return 1;
}

int Del_DupaLG(TLG aL, TF free_elem)
{
	if(aL == NULL || aL->urm == NULL) {
		return 0;
	}

	TLG del = aL->urm;
	aL->urm = del->urm;

	free_elem(del->info);
	free(del);

	return 1;
}

int Del_Elem(TLG *aL, TF free_elem, TFCmp fcmp, void* elem)
{
	if (*aL == NULL) {
		return 0;
	}

	if (fcmp((*aL)->info, elem) == 0) {
		return Del_IncLG(aL, free_elem);
	}

	TLG el = *aL;
	while (el->urm != NULL) {
		if (fcmp(el->urm->info, elem) == 0) {
			return Del_DupaLG(el, free_elem);
		}
		el = el->urm;
	}

	return 0;
}

void* CautareLG(TLG aL, TFCmp fcmp, void *elem)
{
	if (aL == NULL) {
		return NULL;
	}

	TLG el = aL;
	while (el != NULL) {
		if (fcmp(elem, el->info) == 0) {
			return el->info;
		}
		el = el->urm;
	}

	return NULL;
}

void DistrugeLG(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

void Afisare(TLG* aL, TF afiEL, const char* delim)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	// printf("[\n");
	for (; *aL; aL = &(*aL)->urm) {
		afiEL((*aL)->info);
		if ((*aL)->urm != NULL) {
			printf("%s", delim);
		}
    }
	// printf("]\n");
}

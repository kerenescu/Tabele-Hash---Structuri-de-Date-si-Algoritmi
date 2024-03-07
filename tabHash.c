#include "tabHash.h"

typedef struct {
    int lungime;
    TLG sublista;
} TNivel1;

typedef struct {
    char *cuvant;
    int nr_aparitii;
} TNivel2;

TH* InitTH(size_t M, TFHash fh)
{
    TH *h = (TH *) calloc(sizeof(TH), 1);

    if (!h) {
        printf("eroare alocare tabela hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));

    if(!h->v) {
        printf("eroare alocare vector pointeri TLG in tabela hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void free_nivel2(void *info)
{
    TNivel2 *niv2 = (TNivel2 *) info;
    free(niv2->cuvant);
    free(niv2);
}

void free_nivel1(void *info)
{
    TNivel1 *niv1 = (TNivel1 *) info;
    DistrugeLG(&niv1->sublista, free_nivel2);
    free(niv1);
}

void DistrTH(TH **h)
{
    TLG *p;
    int i;
    for (i = 0, p = (*h)->v; i < (*h)->M; i++, p++) {
        DistrugeLG(p, free_nivel1);
    }

    free((*h)->v);
    free(*h);
    *h = NULL;
}

int cmp_nivel1(void *a, void *b)
{
    TNivel1 *niv_a = (TNivel1 *) a;
    TNivel1 *niv_b = (TNivel1 *) b;

    return niv_a->lungime - niv_b->lungime;
}

int cmp_nivel2_cuvinte(void *a, void *b)
{
    TNivel2 *niv_a = (TNivel2 *) a;
    TNivel2 *niv_b = (TNivel2 *) b;

    int ret = strcmp(niv_a->cuvant, niv_b->cuvant);
    return ret;
}

int cmp_nivel2(void *a, void *b)
{
    TNivel2 *niv_a = (TNivel2 *) a;
    TNivel2 *niv_b = (TNivel2 *) b;

    int cmp_lungimi = niv_b->nr_aparitii - niv_a->nr_aparitii;;
    if(cmp_lungimi != 0)
        return cmp_lungimi;

    return strcmp(niv_a->cuvant, niv_b->cuvant);
}

int inserare_nivel2(TLG *l, char *cuv)
{
    // noul nod pentru cuvantul inserat
    TNivel2 *nou = malloc(sizeof(TNivel2));
    nou->cuvant = malloc(strlen(cuv) + 1);
    strcpy(nou->cuvant, cuv);
    nou->nr_aparitii = 1;

    // cautam daca exista cuvantul
    TNivel2 *niv2 = (TNivel2 *)(CautareLG(*l, cmp_nivel2_cuvinte, nou));
    if (niv2 != NULL) {
        nou->nr_aparitii += niv2->nr_aparitii;
        if (Del_Elem(l, free_nivel2, cmp_nivel2_cuvinte, nou) == 0) {
            free(nou);
            return 0;
        }
    }

    // adaugam cuvantul inapoi in lista cu nr aparitii actualizat
    if (Ins_OrdLG(l, cmp_nivel2, nou) == 0) {
        free(nou);
        return 0;
    }

    return 1;
}

int inserare_nivel1(TH *h, char *cuv)
{
    // creare nod nivel1 nou
    TNivel1 *nou = malloc(sizeof(TNivel1));
    nou->lungime = strlen(cuv);
    nou->sublista = NULL;

    int cod = h->fh(cuv);

    // caut daca exista elementul
    TNivel1 *niv1 = (TNivel1 *)(CautareLG(h->v[cod], cmp_nivel1, nou));
    
    if (niv1 != NULL) {
        free(nou);
    } else {
        // daca nu exista lungimea o inserez in lista
        if (Ins_OrdLG(h->v + cod, cmp_nivel1, nou) == 0) {
            free(nou);
            return 0;
        }
        niv1 = nou;
    }

    // inserare cuvant in sublista gasita
    return inserare_nivel2(&niv1->sublista, cuv);
}

int InsTH(TH *h, char *cuv)
{
    return inserare_nivel1(h, cuv);
}

void afi_nivel2(void *elem)
{
    TNivel2 *niv2 = (TNivel2 *)elem;
    printf("%s/%d", niv2->cuvant, niv2->nr_aparitii);
}

void afi_nivel1(void *elem)
{
    TNivel1 *niv1 = (TNivel1 *) elem;
    printf("(%d:", niv1->lungime);
    Afisare(&niv1->sublista, afi_nivel2, ", ");
    printf(")");
}

void afi_nivel1_2(void *elem)
{
    TNivel1 *niv1 = (TNivel1 *) elem;
    printf("(%d: ", niv1->lungime);
    Afisare(&niv1->sublista, afi_nivel2, ", ");
    printf(")");
}

void AfiTH(TH *h)
{
    TLG el;
    int i;
    for (i = 0; i < h->M; i++) {
        el = h->v[i];
        if (el) {
            printf("pos %d: ", i);
            Afisare(&el, afi_nivel1, "");
            printf("\n");
        }
    }
}

void AfiTH_litera_lungime(TH *h, char c, int l)
{
    int cod = h->fh(&c);
    TLG el = h->v[cod];

    if (el == NULL) {
        return;
    }

    TNivel1 *niv1;
    while (el != NULL) {
        niv1 = (TNivel1 *) el->info;
        if(niv1->lungime == l) {
            break;
        }
        el = el->urm;
    }

    if (el != NULL) {
        afi_nivel1(niv1);
        printf("\n");
    }
}

void AfiTH_aparitii_max(TH *h, int n)
{
    TLG el;
    int i;
    for (i = 0; i < h->M; i++) {
        el = h->v[i];
        int afis = 0;

        while (el != NULL) {
            TNivel1 *niv1 = (TNivel1 *) el->info;

            // cautam primul cuvant cu nr de aparitii <= n
            TLG sub_el = niv1->sublista;
            while (sub_el != NULL) {
                TNivel2 *niv2 = (TNivel2 *) sub_el->info;
                if (niv2->nr_aparitii <= n) {
                    break;
                }

                sub_el = sub_el->urm;
            }

            // daca exista, afisam cuvintele incepand cu cel gasit
            if (sub_el != NULL) {
                if (afis == 0) {
                    printf("pos%d: ", i);
                    afis = 1;
                }

                // afisare sublista nivel 1 de la un termen in colo
                TNivel1 afis;
                afis.lungime = niv1->lungime;
                afis.sublista = sub_el;
                afi_nivel1_2(&afis);

                // if(el->urm != NULL) {
                //     printf("");
                // }
            }

            el = el->urm;
        }

        if (afis == 1) {
            printf("\n");
        }
    }
}
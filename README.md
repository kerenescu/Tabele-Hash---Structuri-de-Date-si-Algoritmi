**Student:** Boingiu Keren Ioana

**Grupa:**

# Tema 1 SD: Tabele Hash
## Descriere rezolvare
Folosind implementarea de liste simplu înlănțuite am creat o structură de tip tabelă hash care pentru fiecare valoare a hash-ului trimite la o listă pe două nivele (fiecare nod din lista de pe nivelul 1 trimite către o altă listă). Concret, formula de hash este determinarea index-ului fiecărei litere convertită la literă mică (adică 'a' devine hash-ul 0, 'b' hash-ul 1 etc), iar lista de pe primul nivel conține lungimile cuvintelor, pentru fiecare lungime fiind memorată lista de cuvinte de acea lungime împreună cu numărul de apariții.

Pe baza acestui mod de structurare al datelor sunt implementate funcțiile cerute. Deoarece am folosit liste înlanțuite generice, mare parte dintre funcțiile pentru listele pentru nivelul 1 și nivelul 2 sunt comune și astfel se evită duplicarea codului. Inserarea unui element se face pe două niveluri: la început se caută dacă pe nivelul 1 corespunzător hash-ului cuvântului de adăugat și se crează acel nod dacă nu există, păstrând ordinea listei de pe primul nivel. Mai apoi, în nodul creat sau nodul existent găsit de pe nivelul 1 se inserează cuvântul pe nivelul 2. Inserarea pe al doilea nivel presupune căutarea cuvântului în sublistă și ștergerea acestuia dacă deja există, cu actualizarea numărului de apariții pentru cuvântul de inserat, iar apoi se inserează cuvântul cu noul număr de apariții, păstrând ordinea în sublistă.

Fișierele `tabHash.c` și `tabMain.h` conțin implementarea tabelei Hash, iar `functiiLG.c` și `tlg.h` conțin funcțiile pentru implementarea listei simplu înlănțuite generice. Fișierul `main.c` inițializează structurile de date, preia input-ul de la utilizator și apelează funcțiile corespunzătoare asupra tabelei hash.
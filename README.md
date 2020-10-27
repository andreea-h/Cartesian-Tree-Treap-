# Cartesian-Tree-Treap-
Implementarea unei structuri care sa modeleze o multime de elemente identificate dupa indicele la care acestea se insereaza, imbinand perfomanetele unei liste si ale unui vector (din punct de vedere al timpului de executie pentru operatii de baza precum adaugarea unui nou element, stergere, concatenare).

Pentru implementare am folosit structura Treap(cartesian Treap with implicit key), memorand pentru fiecare nod din arbore 3 informatii: valoarea (numarul introdus in secventa), prioritatea (campul 'priority') = un numar generat aleator, si size = 1 + size(nod->left) + size(nod->right).
Arborele este considerat arbore binar de cautare dupa valorile din campul 'size' si max_heap dupa valorile din campul 'priority'.
Pentru inserarea unui nod in arbore am folosit functiile 'MySplit' si 'concat'. Arborele este construit in asa fel incat operatiile se realizeaza in O(logn), unde n este numarul de noduri din arbore.
Arborele fiind echilibrat, deducem ca inaltimea arborelui este 1  + max(inaltimea subarborelui stang, inaltimea subarborelui drept).

Arborele este arbore binar de cautare, deci subarborele stang contine valori pentru key mai mici decat valoarea din radacina.
Alegand un element i => subarborele stang are i - 1 elemente si cel drept are (n - i) elemente => h(n) = 1 + max(h(i-1), h(n-i)).
Petem calcula media valorilor lui h(n) ca 1/n * (suma valorilor (1 + max(h(i-1), h(n-i)), cu i din intervalul [1, n].

Deducem ca inaltimea arborelui generat ne permite sa efectuam operatiile in O(logn) (operatiile 'concat' si 'MySplit' utilizate la inserarea unui nod in arbore).

Functia 'insert' foloseste 'MySplit' pentru a imparti secventa 'structure' in 2 secvente in functie de valoarea lui index (prima secventa contine elementele de la [0, index-1], iar a doua de la [index, N]); este folosita functia 'concat' pentru a adauga 'new' in secventa (in prima secventa rezultate din operatia 'split'). Deci, complexitatea obtinuta pentru 'insert' este O(logn).


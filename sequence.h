typedef int Type;

typedef struct sequence {
	Type value; //valoarea elementului introdus in secventa
	Type priority; //numar generat aleator
	Type size; //camp folosit pentru deducerea indecsilor la care au fost inserate elementele in secventa
	struct sequence* left;
	struct sequence* right;
} *Sequence;


// Returneaza structura vida
Sequence init() {  //aloca memorie pentru un nod al arborelui
	Sequence sec =(struct sequence*)malloc(sizeof(struct sequence));
	sec->size=1; //initilizeaza campul 'size' cu 1
	return sec;
}

//returneaza valoarea campului 'size' al secventei s
Type get_size(Sequence s) {
	if(s==NULL)
		return 0;
	else
		return s->size;
}

//actualizeaza recursiv valorile campului 'size' pentru nodurile arborelui
void modify_size(Sequence s) {
	if(s==NULL)
		return;
	modify_size(s->left); //actualizeaza valorile campului 'size' in subarborele stang
	if(s!=NULL)
		s->size=1+get_size(s->left)+get_size(s->right);
	modify_size(s->right); //actualizeaza valorile campului size in subarborele drept
}


//Returneaza structura rezultata dupa concatenarea lui struct2 la struct1
Sequence concat(Sequence struct1, Sequence struct2) {
	Sequence rez;
	if(struct1==NULL) {
		return struct2;
	}
	if(struct2==NULL) {
		return struct1;
	}
	if(struct1->priority > struct2->priority) {
		Sequence new;
		// apeleaza recursiv functia de 'concat' pentru subarborle drept al primul arbore primit ca argument
		new=concat(struct1->right, struct2);
		rez=init();
		//pentru arborele rezultat preia valorile campurilor din primul arbore primit ca argument 
		rez->value=struct1->value;
		rez->priority=struct1->priority;
		rez->left=struct1->left;
		rez->right=new;
		modify_size(rez); //actualizeaza valoarea campului 'size' pentru arborele rezultat
		return rez;
	}
	else {
		Sequence new;
		//apeleaza recursiv functia de 'concat' pentru subarborele stang al celui de-al doilea argument
		new=concat(struct1, struct2->left);
		rez=init();
		//pentru arborele rezultat preia valorile campului 'size' pentru al doilea arbore primit ca argument
		rez->value=struct2->value;
		rez->priority=struct2->priority;
		rez->left=new;
		rez->right=struct2->right;
		modify_size(rez);
		return rez;
	}
}

// imparte secventa de elemente 's' in secventele left si right
// left va contine elementele de pe pozitiile [0, index-1] iar right elementele de pe pozitiile [index, s->size]
void MySplit(Sequence s, Sequence* left, Sequence* right, Type key) {
	int current_size;
	if(key==0) {  
		*left=NULL;
		*right=s;
		return;
	}
	//daca subarborii secventei initiale sunt NULL, left va fi arborle initial
	if(s->right==NULL && s->left==NULL) {
		*left=s;
		*right=NULL;
		return;
	}
	if(s->left==NULL) {
		current_size=1;
	}
	else
		current_size=s->left->size+1; //'dimeniunea' suborborelui stang + 1
	Sequence new=init();
	if(current_size<=key) {
	  if(s->right==NULL) {
	  		*left=s;
	  		*right=NULL;
	  		modify_size(*left);
	  		modify_size(*right);
		}
		else {
			//radacina arborelui initial va fi plasata in 'left'
			//recursiv, efectuam 'split' asupra subarborelui drept
			MySplit(s->right,&new,right,key-current_size); 
			(*left)->left=s->left;
			(*left)->right=new;
			(*left)->value=s->value;
			(*left)->priority=s->priority;
			modify_size(*left); //actualizeaza valorile campului 'size' pentru arborii obtinuti
			modify_size(*right);
		}
	}
	else {
		if(s->left==NULL) {
			*left=s;
			*right=NULL;
	  		modify_size(*right);
	  		modify_size(*left);
		}
		else {	
			//radacina arborelui initial va fi plasata in 'right'
			//recursiv, efectuam split asupra subarborelui stang
			MySplit(s->left,left, &new, key);
			(*right)->right=s->right;
			(*right)->left=new;
			(*right)->value=s->value;
			(*right)->priority=s->priority;
			modify_size(*right);
			modify_size(*left);
		}
	}	
}

// Afisarea elementelor din secventa
// se afiseaza arborele 's'- parcurgere in inordine(parcurgerea in inordine corespunde ordinii date de indexarea elementelor structurii)
void afisare(Sequence s) {
	if(s==NULL)
		return;
	afisare(s->left);
	printf("%d  ", s->value);
	afisare(s->right);
}

// Insereaza un element în structura 'structure' la pozitia index
Sequence insert(Sequence structure, Type item, int index) {
	if(structure->size == -1) {  //daca arborele este vid (adica se insereaza primul nod in arbore)
		structure->value=item;
		structure->priority=rand()%100; //genereaza o prioritate random
		structure->size=1;
		return structure;
	}
	Sequence left=init(), right=init();
	//efectueaza 'split' asupra secventei initiale
	//(se imparte secventa in 2 secvente - prima(left) cu elemente de indici [0, index-1] iar a doua de indici [index, N] )
	MySplit(structure, &left, &right,index);
	Sequence new = init(); //new este nodul nou inserat in arbore
	new->value=item;
	new->priority=rand()%100;
	//se concateneaza la prima subsecventa nodul de inserat 'new'
	Sequence rez1=concat(left, new);
	modify_size(rez1); //se actualizeaza valorile campului 'size'
	//se concateneaza subsecventa a doua la rezultatul concatenarii 'rez1'
	Sequence rez2=concat(rez1, right);
	modify_size(rez2);
	return rez2;
}

// Sterge elementul de pe pozitia index din structura
Sequence Delete(Sequence structure, int index) {
	Sequence left=init();
	Sequence right=init();
	MySplit(structure, &left, &right, index); 
	//elementul care trebuie eliminat este primul element din 'right'
	Sequence left1=init();
	Sequence right1=init(); 
	MySplit(right,&left1, &right1,1); //'right' va contine elementul de pe pozitia 'index'
	//secventa rezultata se obtine concatenand 'right1' la 'left'
	Sequence rezultat=concat(left, right1); 
	modify_size(rezultat);
	return rezultat;
}

// Returneaza valoarea primului element din 'structure'
// se considera primul acel element care a fost inserat pe indexul cel mai mic
Type getFirst(Sequence structure) {
	if(structure->left==NULL)
		return structure->value;
	return getFirst(structure->left); //'primul' element se obtine deplasandu-ne mereu prin subarborele stang
}

// Returneaza valoarea elementului de pe pozitia index
Type lookup(Sequence structure, int index) {
	Sequence left=init(), right=init();
	MySplit(structure, &left, &right,index);
	return getFirst(right); //elementul cautat este 'primul' element din arborele 'right' 
	//primul - the leftmost node - nodul cu indexul cel mai mic la inserare
}


//atribuie pentru nodul cel mai din stanga al arborelui valoarea item
void SetValue(Sequence structure, Type item) {
	if(structure->left==NULL) {
			structure->value=item;
		return;
	}
	SetValue(structure->left,item);
}

// Înlocuieste valoarea elementului de pe pozitia index cu item
Sequence set(Sequence structure, Type item, int index) {
	Sequence left=init(), right=init();
	MySplit(structure, &left, &right, index);
	//elementul a carui valoare trebuie modificata este primul din subarborele 'right'
	//'primul' - the leftmost node (nodul cu valoarea cea mai mica a indexului)
	SetValue(right, item); //seteaza valoarea nodului cu indexul 'index' ca fiind item
	//concateneaza  subarborii 'left' si noul 'right'
	structure=concat(left, right);
	return structure;
}

// Returneaza dimensiunea structurii 
int size(Sequence structura) {  
	return structura->size;
}

// Returneaza cele doua structuri rezultate în urma divizarii 
// (rezultatul este retinut într-un Sequence* cu 2 elemente)
Sequence* split(Sequence structure, int index) {
	Sequence* rez= (Sequence *)malloc(2*sizeof(Sequence));
	rez[0]=(Sequence)malloc(sizeof(Sequence));
	rez[1]=(Sequence)malloc(sizeof(Sequence));
	//functia 'MySplit' imparte 'structure' in 2 secvente 'rez[0]' si 'rez[1]'
	MySplit(structure, &rez[0], &rez[1], index+1); 
	//rez[1] va contine elementele din structure incepand de la indexul 'index+1' (inclusiv)
	return rez;
}

#include <bits/stdc++.h>
using namespace std;
int MAX; //size of each node
class BPTree; //self explanatory classes

FILE* f;

class indice
{
public:
	int pos;
	int codigo;
	indice(){
		//codigo="";
		pos=0;
	}
	//~indice();
	bool operator>(indice x){
		return this->codigo > x.codigo;
	}
	bool operator<(indice x){
		return this->codigo < x.codigo;
	}
	indice& operator = (const indice &p){
        if(this!=&p){ //Comprueba que no se esté intentanod igualar un objeto a sí mismo
            this->codigo=p.codigo;
            this->pos=p.pos;
        }
        return *this;
	}
};

class Node
{
	bool IS_LEAF;
	vector<indice> key;
	int size;
	Node** ptr;
	friend class BPTree;
public:
	Node();
};
class BPTree
{
	Node *root;
	void insertInternal(int,int,Node*,Node*);
	void removeInternal(int,Node*,Node*);
	Node* findParent(Node*,Node*);
public:
	BPTree();
	void search(int);
	void insert(int);
	void remove(int);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);
	void insertTXT();
	void inserAux(int x, int p);

	~BPTree();
};
//give command line argument to load a tree from log
//to create a fresh tree, do not give any command line argument
int main(int argc, char* argv[])
{
	BPTree bpt;//B+ tree object that carries out all the operations
	string command;
	int x;
	bool close = false;
	string logBuffer;//used to save into log
	ifstream fin;
	ofstream fout;
	//create tree from log file from command line input
	if(argc > 1)
	{
		fin.open(argv[1]);//open file
		if(!fin.is_open())
		{
			cout<<"File not found\n";
			return 0;
		}
		int i = 1;
		getline(fin, logBuffer, '\0');//copy log from file to logBuffer for saving purpose
		fin.close();
		fin.open(argv[1]);//reopening file
		getline(fin,command);
		stringstream max(command);//first line of log contains the max degree
		max>>MAX;
		while(getline(fin,command))//iterating over every line ie command
		{
			if(!command.substr(0,6).compare("insert"))
			{
				stringstream argument(command.substr(7));
				argument>>x;
				bpt.insertTXT();
			}
			else if(!command.substr(0,6).compare("delete"))
			{
				stringstream argument(command.substr(7));
				argument>>x;
				bpt.remove(x);
			}
			else
			{
				cout<<"Comando desconocido: "<<command<<" en linea #"<<i<<"\n";
				return 0;
			}
			i++;
		}
		cout<<"Arbol cargado de: \""<<argv[1]<<"\"\n";
		fin.close();
	}
	else//create fresh tree
	{
		cout<<"Ingrese max degree\n";
		cin>>command;
		stringstream max(command);
		max>>MAX;
		logBuffer.append(command);
		logBuffer.append("\n");
		cin.clear();
		cin.ignore(1);
	}
	//command line menu
	cout<<"Comandos:\nsearch <valor> para buscar\n";
	cout<<"insert <valor> para insertar\n";
	cout<<"delete <valor> para borrar\n";
	cout<<"display para mostrar arbol\n";
	cout<<"save para guardar\n";
	cout<<"exit para salir\n";
	do
	{
		cout<<"Ingrese comando: ";
		getline(cin,command);
		if(!command.substr(0,6).compare("search"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.search(x);
		}
		else if(!command.substr(0,6).compare("insert"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.insert(x);
			logBuffer.append(command);
			logBuffer.append("\n");
		}
		else if(!command.substr(0,6).compare("delete"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.remove(x);
			logBuffer.append(command);
			logBuffer.append("\n");
		}
		else if(!command.compare("display"))
		{
			bpt.display(bpt.getRoot());
		}
		else if(!command.compare("cargarTXT"))
		{

			bpt.insertTXT();
		}
		else if(!command.compare("save"))
		{
			cout<<"Ingrese nombre de archivo: ";
			string filename;
			cin>>filename;
			fout.open(filename);
			fout<<logBuffer;
			fout.close();
			cout<<"Guardado: \""<<filename<<"\"\n";
			cin.clear();
			cin.ignore(1);
		}
		else if(!command.compare("exit"))
		{
			close = true;
		}
		else
		{
			cout<<"Comando invalido\n";
		}
	}while(!close);
	return 0;
}
Node::Node()
{
	//dynamic memory allocation
	key.resize(MAX);
	ptr = new Node*[MAX+1];
}
BPTree::BPTree()
{
	root = NULL;
}
void BPTree::search(int x)
{
	//search logic
	if(root==NULL)
	{
		//empty
		cout<<"Tree empty\n";
	}
	else
	{
		Node* cursor = root;
		//in the following while loop, cursor will will travel to the leaf node possibly consisting the key
		while(cursor->IS_LEAF == false)
		{
			for(int i = 0; i < cursor->size; i++)
			{
				if(x < cursor->key[i].codigo)
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		for(int i = 0; i < cursor->size; i++)
		{
			if(cursor->key[i].codigo == x)
			{
				cout<<"Encontrado\n";
				////////////////

				////////////////
				return;
			}
		}
		cout<<"No Encontrado\n";
	}
}
void BPTree::insert(int x)
{
	//insert logic
	if(root==NULL)
	{

		root = new Node;
		root->key[0].codigo = x;

		/////////////////////
		f=fopen("tex.txt","rb+");

    	fseek(f,0,2);

    	int pos=ftell(f);

    	root->key[0].pos = pos;

    	string cad="C-";

    	//char *intstr=itoa(x);
    	//string str=string(intstr);
    	stringstream ss;
    	ss<<x;
    	string str=ss.str();



    	cad=cad+str+" ";
    	cout<<"Inserte sucursal: ";
    	cin>>str;
    	cad=cad+str+" ";
    	cout<<"Inserte cantidad: ";
    	cin>>str;
    	cad=cad+str;
    	fprintf(f,"%s\n",cad.c_str());
    	fclose(f);
    	///////////////////

		root->IS_LEAF = true;
		root->size = 1;
		cout<<"Raiz creada\nInsertar "<<x<<" completado\n";
	}
	else
	{
		Node* cursor = root;
		Node* parent;
		//in the following while loop, cursor will will travel to the leaf node possibly consisting the key
		while(cursor->IS_LEAF == false)
		{
			parent = cursor;
			for(int i = 0; i < cursor->size; i++)
			{
				if(x < cursor->key[i].codigo)
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
		//now cursor is the leaf node in which we'll insert the new key
		if(cursor->size < MAX)
		{
			//if cursor is not full
			//find the correct position for new key
			int i = 0;
			while(x > cursor->key[i].codigo && i < cursor->size) i++;
			//make space for new key
			for(int j = cursor->size;j > i; j--)
			{
				cursor->key[j].codigo = cursor->key[j-1].codigo;
			}
			cursor->key[i].codigo = x;

			/////////////////////
			f=fopen("tex.txt","rb+");
	    	fseek(f,0,2);
	    	int pos=ftell(f);
	    	cursor->key[i].pos = pos;

	    	string cad="C-";
	    	//char *intstr=itoa(x);
	    	stringstream ss;
    		ss<<x;
    		string str=ss.str();

	    	//string str=string(intstr);
	    	cad=cad+str+" ";
	    	cout<<"Inserte sucursal: ";
	    	cin>>str;
	    	cad=cad+str+" ";
	    	cout<<"Inserte cantidad: ";
	    	cin>>str;
	    	cad=cad+str;
	    	fprintf(f,"%s\n",cad.c_str());
	    	fclose(f);
	    	///////////////////

			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
			cursor->ptr[cursor->size-1] = NULL;
			cout<<"Insertar "<<x<<" completado\n";
		}
		else
		{
			cout<<"Insertar "<<x<<" completado\n";
			//cout<<"Overflow in leaf node!\nSplitting leaf node\n";
			//overflow condition
			//create new leaf node
			Node* newLeaf = new Node;
			//create a virtual node and insert x into it
			int virtualNode[MAX+1];
			int virtualPos[MAX+1];
			for(int i = 0; i < MAX; i++)
			{
				virtualNode[i] = cursor->key[i].codigo;
				virtualPos[i] = cursor->key[i].pos;
				//cout<<virtualNode[i]<<endl;
			}
			int i = 0, j;
			//cout<<"holi"<<endl;
			while(x > virtualNode[i] && i < MAX) {
                i++;
			}
			//cout<<"holi23"<<endl;
			//make space for new key
			for(int j = MAX+1;j > i; j--)
			{
				virtualNode[j] = virtualNode[j-1];
				virtualPos[j] = virtualPos[j-1];
			}
			virtualNode[i] = x;
			/////////////////////
			f=fopen("tex.txt","rb+");
		    fseek(f,0,2);
		    int pos=ftell(f);

	    	string cad="C-";
	    	//char *intstr=itoa(x);
	    	//string str=string(intstr);
	    	stringstream ss;
    		ss<<x;
    		string str=ss.str();

	    	cad=cad+str+" ";
	    	cout<<"Inserte sucursal: ";
	    	cin>>str;
	    	cad=cad+str+" ";
	    	cout<<"Inserte cantidad: ";
	    	cin>>str;
	    	cad=cad+str;
	    	fprintf(f,"%s\n",cad.c_str());
	    	fclose(f);
	    	///////////////////

			virtualPos[i] = pos;
			newLeaf->IS_LEAF = true;
			//split the cursor into two leaf nodes
			cursor->size = (MAX+1)/2;
			newLeaf->size = MAX+1-(MAX+1)/2;
			//make cursor point to new leaf node
			cursor->ptr[cursor->size] = newLeaf;
			//make new leaf node point to the next leaf node
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;
			//now give elements to new leaf nodes
			for(i = 0; i < cursor->size; i++)
			{
				cursor->key[i].codigo = virtualNode[i];
				cursor->key[i].pos = virtualPos[i];

			}
			for(i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i].codigo = virtualNode[j];
				newLeaf->key[i].pos = virtualPos[j];
			}
			//modify the parent
			if(cursor == root)
			{
				//if cursor is a root node, we create a new root
				Node* newRoot = new Node;
				newRoot->key[0].codigo = newLeaf->key[0].codigo;
				newRoot->key[0].pos = newLeaf->key[0].pos;
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
				cout<<"Nueva raiz creada\n";
			}
			else
			{
				//cout<<"aaaaaaa"<<endl;
				//insert new key in parent node
				insertInternal(newLeaf->key[0].codigo,newLeaf->key[0].pos ,parent,newLeaf);
			}
		}
	}
}

void BPTree::insertTXT(){
	FILE* f;
	f=fopen("registro.txt","rb+");
	char linea[100];
    int pos,x;
    string c;
	while(!feof(f)){
		pos=ftell(f);
        fgets(linea,100,f);
        c=linea;
        c=c.substr(2,5);

        istringstream iss(c);
        iss>>x;

        inserAux(x,pos);
	}
	fclose(f);
}


void BPTree::inserAux(int x, int p)
{
	//insert logic
	if(root==NULL)
	{

		root = new Node;
		root->key[0].codigo = x;

    	root->key[0].pos = p;

		root->IS_LEAF = true;
		root->size = 1;
		cout<<"Raiz creada\nInsertar "<<x<<" completado\n";
	}
	else
	{
		Node* cursor = root;
		Node* parent;
		//in the following while loop, cursor will will travel to the leaf node possibly consisting the key
		while(cursor->IS_LEAF == false)
		{
			parent = cursor;
			for(int i = 0; i < cursor->size; i++)
			{
				if(x < cursor->key[i].codigo)
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
		//now cursor is the leaf node in which we'll insert the new key
		if(cursor->size < MAX)
		{
			//if cursor is not full
			//find the correct position for new key
			int i = 0;
			while(x > cursor->key[i].codigo && i < cursor->size) i++;
			//make space for new key
			for(int j = cursor->size;j > i; j--)
			{
				cursor->key[j].codigo = cursor->key[j-1].codigo;
			}
			cursor->key[i].codigo = x;


	    	cursor->key[i].pos = p;

			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
			cursor->ptr[cursor->size-1] = NULL;
			cout<<"Insertar "<<x<<" completado\n";
		}
		else
		{
			cout<<"Insertar "<<x<<" completado\n";
			//cout<<"Overflow in leaf node!\nSplitting leaf node\n";
			//overflow condition
			//create new leaf node
			Node* newLeaf = new Node;
			//create a virtual node and insert x into it
			int virtualNode[MAX+1];
			int virtualPos[MAX+1];
			for(int i = 0; i < MAX; i++)
			{
				virtualNode[i] = cursor->key[i].codigo;
				virtualPos[i] = cursor->key[i].pos;
				//cout<<virtualNode[i]<<endl;
			}
			int i = 0, j;
			//cout<<"holi"<<endl;
			while(x > virtualNode[i] && i < MAX) {
                i++;
			}
			//cout<<"holi23"<<endl;
			//make space for new key
			for(int j = MAX+1;j > i; j--)
			{
				virtualNode[j] = virtualNode[j-1];
				virtualPos[j] = virtualPos[j-1];
			}
			virtualNode[i] = x;

			virtualPos[i] = p;
			newLeaf->IS_LEAF = true;
			//split the cursor into two leaf nodes
			cursor->size = (MAX+1)/2;
			newLeaf->size = MAX+1-(MAX+1)/2;
			//make cursor point to new leaf node
			cursor->ptr[cursor->size] = newLeaf;
			//make new leaf node point to the next leaf node
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;
			//now give elements to new leaf nodes
			for(i = 0; i < cursor->size; i++)
			{
				cursor->key[i].codigo = virtualNode[i];
				cursor->key[i].pos = virtualPos[i];

			}
			for(i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i].codigo = virtualNode[j];
				newLeaf->key[i].pos = virtualPos[j];
			}
			//modify the parent
			if(cursor == root)
			{
				//if cursor is a root node, we create a new root
				Node* newRoot = new Node;
				newRoot->key[0].codigo = newLeaf->key[0].codigo;
				newRoot->key[0].pos = newLeaf->key[0].pos;
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
				cout<<"Nueva raiz creada\n";
			}
			else
			{
				//cout<<"aaaaaaa"<<endl;
				//insert new key in parent node
				insertInternal(newLeaf->key[0].codigo,newLeaf->key[0].pos ,parent,newLeaf);
			}
		}
	}
}


void BPTree::insertInternal(int x, int p, Node* cursor, Node* child)
{
	if(cursor->size < MAX)
	{
		//if cursor is not full
		//find the correct position for new key
		int i = 0;
		while(x > cursor->key[i].codigo && i < cursor->size) i++;
		//make space for new key
		for(int j = cursor->size;j > i; j--)
		{
			cursor->key[j].codigo = cursor->key[j-1].codigo;
			cursor->key[j].pos = cursor->key[j-1].pos;
		}//make space for new pointer
		for(int j = cursor->size+1; j > i+1; j--)
		{
			cursor->ptr[j] = cursor->ptr[j-1];
		}
		cursor->key[i].codigo = x;
		cursor->key[i].pos = p;
		cursor->size++;
		cursor->ptr[i+1] = child;
		//cout<<"Inserted key in an Internal node successfully\n";
	}
	else
	{
		//cout<<"Inserted key in an Internal node successfully\n";
		//cout<<"Overflow in internal node!\nSplitting internal node\n";
		//if overflow in internal node
		//create new internal node
		Node* newInternal = new Node;
		//create virtual Internal Node;
		int virtualKey[MAX+1];
		int virtualP[MAX+1];
		Node* virtualPtr[MAX+2];
		for(int i = 0; i < MAX; i++)
		{
			virtualKey[i] = cursor->key[i].codigo;
			virtualP[i] = cursor->key[i].pos;
		}
		for(int i = 0; i < MAX+1; i++)
		{
			virtualPtr[i] = cursor->ptr[i];
		}
		int i = 0, j;
		while(x > virtualKey[i] && i < MAX) i++;
		//make space for new key
		for(int j = MAX+1;j > i; j--)
		{
			virtualKey[j] = virtualKey[j-1];
			virtualP[j] = virtualP[j-1];
		}
		virtualKey[i] = x;
		virtualP[i] = p;
		//make space for new ptr
		for(int j = MAX+2;j > i+1; j--)
		{
			virtualPtr[j] = virtualPtr[j-1];
		}
		virtualPtr[i+1] = child;
		newInternal->IS_LEAF = false;
		//split cursor into two nodes
		cursor->size = (MAX+1)/2;
		newInternal->size = MAX-(MAX+1)/2;
		//give elements and pointers to the new node
		for(i = 0, j = cursor->size+1; i < newInternal->size; i++, j++)
		{
			newInternal->key[i].codigo = virtualKey[j];
			newInternal->key[i].pos = virtualP[j];
		}
		for(i = 0, j = cursor->size+1; i < newInternal->size+1; i++, j++)
		{
			newInternal->ptr[i] = virtualPtr[j];
		}
		// m = cursor->key[cursor->size]
		if(cursor == root)
		{
			//if cursor is a root node, we create a new root
			Node* newRoot = new Node;
			newRoot->key[0].codigo = cursor->key[cursor->size].codigo;
			newRoot->key[0].pos = cursor->key[cursor->size].pos;
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
			cout<<"Raiz creada\n";
		}
		else
		{
			//recursion
			//find depth first search to find parent of cursor
			insertInternal(cursor->key[cursor->size].codigo ,cursor->key[cursor->size].pos,findParent(root,cursor) ,cursor);
		}
	}
}
Node* BPTree::findParent(Node* cursor, Node* child)
{
	//finds parent using depth first traversal and ignores leaf nodes as they cannot be parents
	//also ignores second last level because we will never find parent of a leaf node during insertion using this function
	Node* parent;
	if(cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
	{
		return NULL;
	}
	for(int i = 0; i < cursor->size+1; i++)
	{
		if(cursor->ptr[i] == child)
		{
			parent = cursor;
			return parent;
		}
		else
		{
			parent = findParent(cursor->ptr[i],child);
		}
	}
	return parent;
}
void BPTree::remove(int x)
{
	//delete logic
	if(root==NULL)
	{
		cout<<"Arbol vacio\n";
	}
	else
	{
		Node* cursor = root;
		Node* parent;
		int leftSibling, rightSibling;
		//in the following while loop, cursor will will travel to the leaf node possibly consisting the key
		while(cursor->IS_LEAF == false)
		{
			for(int i = 0; i < cursor->size; i++)
			{
				parent = cursor;
				leftSibling = i-1; //leftSibling is the index of left sibling in the parent node
				rightSibling =  i+1; //rightSibling is the index of right sibling in the parent node
				if(x < cursor->key[i].codigo)
				{
					cursor = cursor->ptr[i];
					break;
				}
				if(i == cursor->size - 1)
				{
					leftSibling = i;
					rightSibling = i+2;
					cursor = cursor->ptr[i+1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		bool found = false;
		int pos;
		for(pos = 0; pos < cursor->size; pos++)
		{
			if(cursor->key[pos].codigo == x)
			{
				found = true;
				break;
			}
		}
		if(!found)//if key does not exist in that leaf node
		{
			cout<<"No Encontrado\n";
			return;
		}
		//deleting the key
		for(int i = pos; i < cursor->size; i++)
		{
			cursor->key[i].codigo = cursor->key[i+1].codigo;
		}
		cursor->size--;
		if(cursor == root)//if it is root node, then make all pointers NULL
		{
			//cout<<"Deleted "<<x<<" from leaf node successfully\n";
			for(int i = 0; i < MAX+1; i++)
			{
				cursor->ptr[i] = NULL;
			}
			if(cursor->size == 0)//if all keys are deleted
			{
				cout<<"Arbol muerto\n";
				cursor->key.clear();
				delete[] cursor->ptr;
				delete cursor;
				root = NULL;
			}
			return;
		}
		cursor->ptr[cursor->size] = cursor->ptr[cursor->size+1];
		cursor->ptr[cursor->size+1] = NULL;
		//cout<<"Deleted "<<x<<" from leaf node successfully\n";
		if(cursor->size >= (MAX+1)/2)//no underflow
		{
			return;
		}
		//cout<<"Underflow in leaf node!\n";
		//underflow condition
		//first we try to transfer a key from sibling node
		//check if left sibling exists
		if(leftSibling >= 0)
		{
			Node *leftNode = parent->ptr[leftSibling];
			//check if it is possible to transfer
			if(leftNode->size >= (MAX+1)/2+1)
			{
				//make space for transfer
				for(int i = cursor->size; i > 0; i--)
				{
					cursor->key[i].codigo = cursor->key[i-1].codigo;
				}
				//shift pointer to next leaf
				cursor->size++;
				cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
				cursor->ptr[cursor->size-1] = NULL;
				//transfer
				cursor->key[0].codigo = leftNode->key[leftNode->size-1].codigo;
				//shift pointer of leftsibling
				leftNode->size--;
				leftNode->ptr[leftNode->size] = cursor;
				leftNode->ptr[leftNode->size+1] = NULL;
				//update parent
				parent->key[leftSibling].codigo = cursor->key[0].codigo;
				//cout<<"Transferred "<<cursor->key[0].codigo<<" from left sibling of leaf node\n";
				return;
			}
		}
		if(rightSibling <= parent->size)//chech if right sibling exist
		{
			Node *rightNode = parent->ptr[rightSibling];
			//check if it is possible to transfer
			if(rightNode->size >= (MAX+1)/2+1)
			{
				//shift pointer to next leaf
				cursor->size++;
				cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
				cursor->ptr[cursor->size-1] = NULL;
				//transfer
				cursor->key[cursor->size-1].codigo = rightNode->key[0].codigo;
				//shift pointer of rightsibling
				rightNode->size--;
				rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size+1];
				rightNode->ptr[rightNode->size+1] = NULL;
				//shift conent of right sibling
				for(int i = 0; i < rightNode->size; i++)
				{
					rightNode->key[i].codigo = rightNode->key[i+1].codigo;
				}
				//update parent
				parent->key[rightSibling-1].codigo = rightNode->key[0].codigo;
				//cout<<"Transferred "<<cursor->key[cursor->size-1].codigo<<" from right sibling of leaf node\n";
				return;
			}
		}
		//must merge and delete a node
		if(leftSibling >= 0)//if left sibling exist
		{
			Node* leftNode = parent->ptr[leftSibling];
			// transfer all keys to leftsibling and then transfer pointer to next leaf node
			for(int i = leftNode->size, j = 0; j < cursor->size; i++, j++)
			{
				leftNode->key[i] = cursor->key[j];
			}
			leftNode->ptr[leftNode->size] = NULL;
			leftNode->size += cursor->size;
			leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
			//cout<<"Merging two leaf nodes\n";
			removeInternal(parent->key[leftSibling].codigo,parent,cursor);// delete parent node key
			cursor->key.clear();
			delete[] cursor->ptr;
			delete cursor;
		}
		else if(rightSibling <= parent->size)//if right sibling exist
		{
			Node* rightNode = parent->ptr[rightSibling];
			// transfer all keys to cursor and then transfer pointer to next leaf node
			for(int i = cursor->size, j = 0; j < rightNode->size; i++, j++)
			{
				cursor->key[i].codigo = rightNode->key[j].codigo;
			}
			cursor->ptr[cursor->size] = NULL;
			cursor->size += rightNode->size;
			cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
			//cout<<"Merging two leaf nodes\n";
			removeInternal(parent->key[leftSibling+1].codigo,parent,rightNode);// delete parent node key
			rightNode->key.clear();
			delete[] rightNode->ptr;
			delete rightNode;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void BPTree::removeInternal(int x, Node* cursor, Node* child)
{
	//deleting the key x first
	//checking if key from root is to be deleted
	if(cursor == root)
	{
		if(cursor->size == 1)//if only one key is left, change root
		{
			if(cursor->ptr[1] == child)
			{
				child->key.clear();
				delete[] child->ptr;
				delete child;
				root = cursor->ptr[0];
				cursor->key.clear();
				delete[] cursor->ptr;
				delete cursor;
				//cout<<"Changed root node\n";
				return;
			}
			else if(cursor->ptr[0] == child)
			{
				child->key.clear();
				delete[] child->ptr;
				delete child;
				root = cursor->ptr[1];
				cursor->key.clear();
				delete[] cursor->ptr;
				delete cursor;
				//cout<<"Changed root node\n";
				return;
			}
		}
	}
	int pos;
	for(pos = 0; pos < cursor->size; pos++)
	{
		if(cursor->key[pos].codigo == x)
		{
			break;
		}
	}
	for(int i = pos; i < cursor->size; i++)
	{
		cursor->key[i].codigo = cursor->key[i+1].codigo;
	}
	//now deleting the pointer child
	for(pos = 0; pos < cursor->size+1; pos++)
	{
		if(cursor->ptr[pos] == child)
		{
			break;
		}
	}
	for(int i = pos; i < cursor->size+1; i++)
	{
		cursor->ptr[i] = cursor->ptr[i+1];
	}
	cursor->size--;
	if(cursor->size >= (MAX+1)/2-1)//no underflow
	{
		//cout<<"Deleted "<<x<<" from internal node successfully\n";
		return;
	}
	//cout<<"Underflow in internal node!\n";
	//underflow, try to transfer first
	Node* parent = findParent(root, cursor);
	int leftSibling, rightSibling;
	//finding left n right sibling of cursor
	for(pos = 0; pos < parent->size+1; pos++)
	{
		if(parent->ptr[pos] == cursor)
		{
			leftSibling = pos - 1;
			rightSibling = pos + 1;
			break;
		}
	}
	//try to transfer
	if(leftSibling >= 0)//if left sibling exists
	{
		Node *leftNode = parent->ptr[leftSibling];
		//check if it is possible to transfer
		if(leftNode->size >= (MAX+1)/2)
		{
			//make space for transfer of key
			for(int i = cursor->size; i > 0; i--)
			{
				cursor->key[i].codigo = cursor->key[i-1].codigo;
			}
			//transfer key from left sibling through parent
			cursor->key[0].codigo = parent->key[leftSibling].codigo;
			parent->key[leftSibling].codigo = leftNode->key[leftNode->size-1].codigo;
			//transfer last pointer from leftnode to cursor
			//make space for transfer of ptr
			for (int i = cursor->size+1; i > 0; i--)
			{
				cursor->ptr[i] = cursor->ptr[i-1];
			}
			//transfer ptr
			cursor->ptr[0] = leftNode->ptr[leftNode->size];
			cursor->size++;
			leftNode->size--;
			//cout<<"Transferred "<<cursor->key[0].codigo<<" from left sibling of internal node\n";
			return;
		}
	}
	if(rightSibling <= parent->size)//check if right sibling exist
	{
		Node *rightNode = parent->ptr[rightSibling];
		//check if it is possible to transfer
		if(rightNode->size >= (MAX+1)/2)
		{
			//transfer key from right sibling through parent
			cursor->key[cursor->size].codigo = parent->key[pos].codigo;
			parent->key[pos].codigo = rightNode->key[0].codigo;
			for (int i = 0; i < rightNode->size -1; i++)
			{
				rightNode->key[i].codigo = rightNode->key[i+1].codigo;
			}
			//transfer first pointer from rightnode to cursor
			//transfer ptr
			cursor->ptr[cursor->size+1] = rightNode->ptr[0];
			for (int i = 0; i < rightNode->size; ++i)
			{
				rightNode->ptr[i] = rightNode->ptr[i+1];
			}
			cursor->size++;
			rightNode->size--;
			//cout<<"Transferred "<<cursor->key[0].codigo<<" from right sibling of internal node\n";
			return;
		}
	}
	//transfer wasnt posssible hence do merging
	if(leftSibling >= 0)
	{
		//leftnode + parent key + cursor
		Node *leftNode = parent->ptr[leftSibling];
		leftNode->key[leftNode->size].codigo = parent->key[leftSibling].codigo;
		for(int i = leftNode->size+1, j = 0; j < cursor->size; j++)
		{
			leftNode->key[i].codigo = cursor->key[j].codigo;
		}
		for(int i = leftNode->size+1, j = 0; j < cursor->size; j++)
		{
			leftNode->ptr[i] = cursor->ptr[j];
			cursor->ptr[j] = NULL;
		}
		leftNode->size += cursor->size+1;
		cursor->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling].codigo, parent, cursor);
		//cout<<"Merged with left sibling\n";

	}
	else if(rightSibling <= parent->size)
	{
		//cursor + parent key + rightnode
		Node *rightNode = parent->ptr[rightSibling];
		cursor->key[cursor->size].codigo = parent->key[leftSibling].codigo;
		for(int i = cursor->size+1, j = 0; j < rightNode->size; j++)
		{
			cursor->key[i].codigo = rightNode->key[j].codigo;
		}
		for(int i = cursor->size+1, j = 0; j < rightNode->size; j++)
		{
			cursor->ptr[i] = rightNode->ptr[j];
			rightNode->ptr[j] = NULL;
		}
		cursor->size += rightNode->size+1;
		rightNode->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling].codigo, parent, rightNode);
		//cout<<"Merged with right sibling\n";
	}
}
void BPTree::display(Node* cursor)
{
	//depth first display
	if(cursor!=NULL)
	{
		for(int i = 0; i < cursor->size; i++)
		{
			cout<<cursor->key[i].codigo<<" ";
		}
		cout<<"\n";
		if(cursor->IS_LEAF != true)
		{
			for(int i = 0; i < cursor->size+1; i++)
			{
				display(cursor->ptr[i]);
			}
		}
	}
}
Node* BPTree::getRoot()
{
	return root;
}
void BPTree::cleanUp(Node* cursor)
{
	//clean up logic
	if(cursor!=NULL)
	{
		if(cursor->IS_LEAF != true)
		{
			for(int i = 0; i < cursor->size+1; i++)
			{
				cleanUp(cursor->ptr[i]);
			}
		}
		for(int i = 0; i < cursor->size; i++)
		{
			cout<<"Deleted key from memory: "<<cursor->key[i].codigo<<"\n";
		}
		cursor->key.clear();
		delete[] cursor->ptr;
		delete cursor;
	}
}
BPTree::~BPTree()
{
	//calling cleanUp routine
	cleanUp(root);
}

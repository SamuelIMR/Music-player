#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;
#include "Cancion.h"
#include "Imagenes.h"

class Lista{
    private:
        class Nodo{
            public:

                Cancion song;
                Nodo *next;
                Nodo *prev;
        };
        Nodo *head;
        Nodo *actual;
        int pos;
        int id;
        void actualizarPos();
    public:
        Lista();
        ~Lista();
        //void insertFirst(Cancion);
        void insertLast(Cancion);
        bool isEmpty();
        void desplegar();
        int travel();
        void siguiente();
        void anterior();
        void eliminar(const int&);
        Cancion buscar(const int&);
        void modificar(int,Cancion);
        void imprimir(int,Cancion);
        void imprimirActual();
        //void play();
        void reproducir();
        void llenar();
        void invertir();
        bool repetido(string, string );

};


void gotoxy(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

Lista::Lista() {
    head=nullptr;
    pos=5;
    id=1;
    }

Lista::~Lista() {
    if(head!=nullptr) {
        Nodo *temp=head->next;
        Nodo *temp2;
        while(temp!=head) {
            temp2=temp;
            temp=temp->next;
            delete temp2;
            }
        delete head;
        }
    }

 /*
void Lista::insertarPrimero(Cancion cancion) {
    Nodo *nuevo=new Nodo();
    nuevo->song= cancion;
    nuevo->song.pos= this->pos;
    pos++;
    if(head == nullptr) {
        nuevo->next=nuevo;
        nuevo->prev= nuevo;
        head=nuevo;
        }
    else {
        Nodo *last = head->prev;
        nuevo->next=head;
        nuevo->prev=last;
        head->prev=nuevo;
        last->next=nuevo;
        head=nuevo;
        }
    actual=nuevo;

}*/

void Lista::insertLast(Cancion cancion) {
    Nodo *nuevo=new Nodo();

    nuevo->song= cancion;
    nuevo->song.pos= this->pos;
    //Ingresar ID
    nuevo->song.setID(id++);
    pos++;
    if(head == nullptr) {
        nuevo->next=nuevo;
        nuevo->prev= nuevo;
        head=nuevo;
        }
    else {
        Nodo *last = head->prev;
        nuevo->next=head;
        nuevo->prev=last;
        head->prev=nuevo;
        last->next=nuevo;

        }
    actual=nuevo;
}

bool Lista::isEmpty() {
    if(head==nullptr) {
        return true;
        }
    else {
        return false;
        }
    }

void Lista::desplegar() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!isEmpty()) {
        int n(5),a;
        int id(1);
        Nodo *temp=head;
        SetConsoleTextAttribute(hConsole, 13);
        gotoxy(46, actual->song.pos);
        cout<<"->";
        SetConsoleTextAttribute(hConsole, 15);
        Cancion cancion;
        do {
            cancion =temp->song;

            gotoxy(50,2);
            for(int i=48; i<=130; i++)
                cout<<"-";


            gotoxy(50, 3);
            cout<< "ID  |   Nombre     |     Artista    |     Album    |   Genero    |    Direccion   |";

            gotoxy(50,4);
            for(int i=48; i<=130; i++)
                cout<<"-";
            if(n == actual->song.pos)
                SetConsoleTextAttribute(hConsole, 13);

            gotoxy(50, n);
            cout<<id<<"   |";
            gotoxy(58, n);
            cout<<cancion.getNombre();
            gotoxy(74, n);
            cout<<cancion.getAutor();
            gotoxy(90, n);
            cout<<cancion.getAlbum();
            gotoxy(106, n);
            cout<<cancion.getGenero();
            gotoxy(120, n);
            cout<<cancion.getDireccion();
            SetConsoleTextAttribute(hConsole, 15);
            temp=temp->next;
            n++;
            id++;

            }while(temp!= head);
        gotoxy(50,n+1);
        for(int i=48; i<=130; i++)
            cout<<"-";



        }
    else {
        gotoxy(50,5);
        cout<< "La lista esta vacia"<<endl;
        }
    }

int Lista::travel() {
    int contador=0;
    if(!isEmpty()) {
        Nodo *temp=head;
        do {
            contador++;
            temp=temp->next;
            }
        while(temp!=head);
        }
    return contador;
    }

void Lista::eliminar(const int& posicion) {
    if(head!=nullptr){
        if(posicion<=travel()) {
            if(posicion==1) {
                if(travel()==1) {
                    delete head;
                    head=nullptr;
                    }
                else {
                    Nodo *tempo = head;
                    Nodo *last =head->prev;
                    head=head->next;
                    last->next=head;
                    head->prev=last;
                    delete tempo;
                    }
                }
            else {
                Nodo *temp=head;
                for(int i=1; i<=posicion-1; i++) {
                    temp=temp->next;
                    }
                Nodo *tempo=temp;
                Nodo *anterior=temp->prev;
                temp=temp->next;
                anterior->next=temp;
                temp->prev=anterior;
                delete tempo;
                }
            }
        pos--;
        id--;
        actualizarPos();
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

Cancion Lista::buscar(const int& posicion) {
    if(head!=nullptr){
        Nodo *temp =head;
        for(int i =1; i<=posicion; i++) {
            temp=temp->next;
        }
        return temp->song;
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}


void Lista::modificar(int id, Cancion c) {
    if(head!=nullptr){
        if(!this->isEmpty()) {
            Nodo* aux(head);
            int pos ;

            do {
                if(aux->song.getID() == id) {
                    pos=aux->song.pos;
                    aux->song=c;
                    aux->song.pos=pos;

                    return;
                }
                aux=aux->next;
            }while(aux!=head);
        }
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

void Lista::imprimir(int puntero, Cancion cancion) {
    Nodo* temp = head;
    if(puntero <= travel() && puntero>=1) {
        if(puntero==1) {
            if(travel()==1) {
                cancion = temp->song;
                gotoxy(60,15);
                cout<<"Nombre: " << cancion.getNombre();
                gotoxy(60,16);
                cout<<"Artista: " << cancion.getAutor();
                gotoxy(60,17);
                cout<<"Album: " << cancion.getAlbum();
                gotoxy(60,18);
                cout<<"Genero: " << cancion.getGenero();
                }
            else {
                cancion = temp->song;
                gotoxy(60,15);
                cout<<"Nombre: " << cancion.getNombre();
                gotoxy(60,16);
                cout<<"Artista: " << cancion.getAutor();
                gotoxy(60,17);
                cout<<"Album: " << cancion.getAlbum();
                gotoxy(60,18);
                cout<<"Genero: " << cancion.getGenero();
                }
            }
        else {
            for(int i=1; i<puntero; i++) {
                temp = temp->next;
                cancion = temp->song;
                }
            gotoxy(60,15);
            cout<<"Nombre: " << cancion.getNombre();
            gotoxy(60,16);
            cout<<"Artista: " << cancion.getAutor();
            gotoxy(60,17);
            cout<<"Album: " << cancion.getAlbum();
            gotoxy(60,18);
            cout<<"Genero: " << cancion.getGenero();
            }
        }

    }

void Lista:: imprimirActual() {
    if(head!=nullptr){
        gotoxy(70, 19);
        cout<< "|-----------------------------------|"<<endl;
        gotoxy(70, 20);
        cout<<"|  Nombre: " <<actual->song.getNombre();
        gotoxy(105,20);
        cout<< " |";
        gotoxy(70, 21);
        cout<< "|-----------------------------------|";
        gotoxy(70, 22);
        cout<< "|  Artista: "<<actual->song.getAutor();
        gotoxy(105,22);
        cout<< " |";
        gotoxy(70, 23);
        cout<< "|-----------------------------------|";
        gotoxy(70, 24);
        cout<< "|  Album: "<<actual->song.getAlbum();
        gotoxy(105,24);
        cout<< " |";
        gotoxy(70, 25);
        cout<< "|-----------------------------------|";
        gotoxy(70, 26);
        cout<< "|  Genero: "<<actual->song.getGenero();
        gotoxy(105,26);
        cout<< " |";
        gotoxy(70, 27);
        cout<< "|-----------------------------------|";
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}


void Lista::siguiente() {
    if(head!=nullptr){
        actual=actual->next;
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

void Lista::anterior() {
    if(head!=nullptr){
        actual=actual->prev;
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

void Lista::reproducir() {
    if(head!=nullptr){
        string s=actual->song.getDireccion();
        int n= s.length();
        char char_array[n+1];
        strcpy(char_array, s.c_str());
        for(int i=0; i<n; i++) {
            cout<< char_array[i];
            }

        PlaySound(TEXT(char_array), NULL, SND_FILENAME | SND_ASYNC);
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

void Lista:: llenar() {
    Cancion cancion;
    string nombre= "Gods plan";
    string artista= "Drake";
    string album= "Scorpion";
    string genero="Rap";
    cancion.setNombre(nombre);
    cancion.setAutor(artista);
    cancion.setAlbum(album);
    cancion.setGenero(genero);
    cancion.setDireccion("7-GodsPlan.wav");
    this->insertLast(cancion);

    string nombre1 ="Sunflower";
    string artista1= "Post Malone";
    string album1= "SpiderMan";
    string genero1= "Hip Hop";
    cancion.setNombre(nombre1);
    cancion.setAutor(artista1);
    cancion.setAlbum(album1);
    cancion.setGenero(genero1);
    cancion.setDireccion("6-Sunflower.wav");
    this->insertLast(cancion);

    string nombre2= "Without me";
    string artista2="Eminem";
    string album2="Eminem show";
    string genero2="Rap";
    cancion.setNombre(nombre2);
    cancion.setAutor(artista2);
    cancion.setAlbum(album2);
    cancion.setGenero(genero2);
    cancion.setDireccion("3-WithoutMe.wav");
    this->insertLast(cancion);

    string nombre3= "Solia";
    string artista3="Bad Bunny";
    string album3="YHLQMDLG";
    string genero3="Reggaeton";
    cancion.setNombre(nombre3);
    cancion.setAutor(artista3);
    cancion.setAlbum(album3);
    cancion.setGenero(genero3);
    cancion.setDireccion("1-Solia.wav");
    this->insertLast(cancion);

    string nombre4= "U M D P";
    string artista4="Vicente F.";
    string album4="Para siempre";
    string genero4="Mariachi";
    cancion.setNombre(nombre4);
    cancion.setAutor(artista4);
    cancion.setAlbum(album4);
    cancion.setGenero(genero4);
    cancion.setDireccion("8-UnMDeP.wav");
    this->insertLast(cancion);

    }

void Lista::invertir() {

    if(head != NULL) {
        Nodo* prevNode = head;
        Nodo* tempNode = head;
        Nodo* curNode = head->next;


        prevNode->prev = prevNode;

        while(curNode != head) {

            tempNode = curNode->next;

            curNode->next = prevNode;
            prevNode->prev = curNode;
            head->next = curNode;
            curNode->prev = head;

            prevNode = curNode;
            curNode = tempNode;
            }


        head = prevNode;
        actual= prevNode;
        actualizarPos();
    }
    else{
        cout<< "Playlist vacia"<<endl;
        system("pause");
        system("cls");
    }
}

void Lista::actualizarPos() {

    Nodo *index(head);
    int i(5),id(1);
    do {
        index->song.pos=i;
        index->song.setID(id);
        index=index->next;
        id++;
        i++;
        }
    while(index!=head);

    actual=head;
    this->desplegar();
}

bool Lista::repetido(string d, string c){
    Nodo *aux (head);

    do{
        if(aux->song.getDireccion()==d || aux->song.getNombre()==c){
            return true;
        }
        aux=aux->next;
    }while(aux!=head);
    return false;
}





#endif // LISTA_H_INCLUDED

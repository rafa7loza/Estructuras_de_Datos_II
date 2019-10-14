#include <iostream>
#include <string>
#include <ClassA.h>
#include <fstream>
using namespace std;

void toFile(ClassA obj, string file){
    ofstream fout;
    fout.open(file,ios::app|ios::binary);
    string cadena = obj.getCadena();
    int campo  = cadena.length();
    int entero = obj.getEntero();
    int tamanioObj;

    tamanioObj = 7*sizeof(int)+campo+1;
    //fout.write( (char *) &campo, sizeof(int));

    fout.write( (char *) &tamanioObj, sizeof(int));
    fout.write( (char *) &entero, sizeof(int));
    fout.write( (char *) &campo, sizeof(int));

    char s[campo + 1];
    for(int i = 0; i  < campo; i++){
        s[i] = cadena[i];
    }
    s[campo] = '\0';
    fout.write(s, campo+1);

    int A[5];
    obj.getA(A);
    
    fout.write( (char *) A, sizeof(int)*5);

    fout.close();

}

ClassA fromFile(int i, string file){
    int campo;
    int entero;
    int A[5];
    int tamanio;
    int cont = 1;
    string cadena;
    ifstream fin;
    fin.open(file,ios::binary);
    fin.read((char *) &tamanio, sizeof(int));
    while(cont<i){
        cout<<"posición del registro : "<<cont<<": "<<fin.tellg()<<endl;
        fin.seekg(tamanio,ios::cur);
        cont++;
        fin.read((char *) &tamanio, sizeof(int));

    }
    fin.read((char *) &entero, sizeof(int));
    fin.read((char *) &campo, sizeof(int));
    char s[campo+1];
    fin.read(s, campo+1);
    cadena = s;
    //cout<<"s: "<<s<<endl;
    //cout<<"Debugging"<<endl;
    //fin.read((char*)&cadena, sizeof(string));
    //cout<<"cadena de lectura: "<<cadena<<endl;
    fin.read((char *) A, sizeof(int)*5);

    cout<<"entero leido: "<<entero<<endl;
    cout<<"campo leido: "<<campo<<endl;
    cout<<"arreglo leido: [";
    for (int i = 0; i<5; i++)
        cout<<" "<<A[i];
    cout<<" ]"<<endl;

    ClassA o(entero, cadena, A);
    return o;
}

int main()
{
    int a[5];
    for (int i = 0; i<5; i++)
        a[i] = 1;
    ClassA obj1(1,"uno", a);
    toFile(obj1,"archivo.txt");
    for (int i = 0; i<5; i++)
        a[i] = 2;
    ClassA obj2(2,"dos", a);
    toFile(obj2,"archivo.txt");
    for (int i = 0; i<5; i++)
        a[i] = 3;
    ClassA obj3(3,"tres", a);
    toFile(obj3,"archivo.txt");
    cout<<"En mem. principal:"<<endl;
    //cout<<"obj1: "<<obj1.getCadena()<<endl;

    cout<<obj1.toString()<<endl;
    cout<<obj2.toString()<<endl;
    cout<<obj3.toString()<<endl;



    ClassA obj_1 = fromFile(1,"archivo.txt");
    ClassA obj_2 = fromFile(2,"archivo.txt");
    ClassA obj_3 = fromFile(3,"archivo.txt");
    cout<<"desde mem. secundaria:"<<endl;
    cout<<obj_1.toString()<<endl;
    cout<<obj_2.toString()<<endl;
    cout<<obj_3.toString()<<endl;

    cout << "Exito" << endl;
    return 0;
}

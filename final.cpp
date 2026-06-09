// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
using namespace std;
class Pessoa {
    private:
        string nome;
    public:
        Pessoa(string n){
            nome=n;
        }
        string getNome(){
            return nome;
        }
    
};
class Aluno:public Pessoa{
    private:
        int matricula;
    public:
        Aluno(string n, int m) : Pessoa(n)
        { 
            matricula = m;
        }
        int getMatricula()
        {
            return matricula;
        }
};
class Bibliotecaria:public Pessoa{
    private:
        int registro_interno;
    public:
        Bibliotecaria(string n, int ri) : Pessoa(n)
        {
            registro_interno=ri;
        }
        int getRegistro_interno(){
            return registro_interno;
        }
    Bibliotecaria jurema("jurema",28072006);
    
};
class Livro{
    private:
        string nome,autor,codigo;
        int ano_publicacao;
    public:
        Livro(string n, string atr, string cod, int ano){
            nome=n;
            autor=atr;
            codigo=cod;
            ano_publicacao=ano;
        }
        string getNome(){
            return nome;
        }
        string getAutor(){
            return autor;
        }
        string getCodigo(){
            return codigo;
        }
        int getAno_publicacao(){
            return ano_publicacao;
        }
};


int main() {
   int login;            
   cout<<"==================+=================="<<endl;
   cout<<"Bem vindo ao  de Biblioteca"<<endl;
   cout<<endl;
   cout<<"escolha seu tipo de acesso"<<endl;
   cout<<"1 para aluno"<<endl;
   cout<<"2 para bibliotecaria"<<endl;
   cin>>login;
   cout<<endl;
   cout<<"==================+=================="<<endl;
 
   
    return 0;
}


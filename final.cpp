//Professor Tiago, enchi de comentários pra deixar tudo bem explicado 
#include <iostream>
#include <string>

using namespace std;

// Classe que retorna erro simples

class ErroSistema {
public:
    string msg;

    ErroSistema(string m) {
        msg = m;
    }
};

// Armazena nome, é herdada por Aluno e Bibilotecaria

class Pessoa {
private:
    string nome;

public:
    Pessoa(string n) {
        nome = n;
    }

    string getNome() {
        return nome;
    }
};

// Armazena a matricula, possui o construtor que usa Pessoa.nome e matricula como "parâmetros" e getMatricula pra retornar num da matricula
class Aluno : public Pessoa {
private:
    int matricula;

public:
    Aluno(string n, int m) : Pessoa(n) {
        matricula = m;
    }

    int getMatricula() {
        return matricula;
    }
};

// Armazena a registro, possui o construtor que usa Pessoa.nome e registro como "parâmetros" e getRegistro pra retornar o num do registro

class Bibliotecaria : public Pessoa {
private:
    int registro;

public:
    Bibliotecaria(string n, int r) : Pessoa(n) {
        registro = r;
    }

    int getRegistro() {
        return registro;
    }
};

// Armazena nome, autor, codigo e ano, possui construtor que usa nome, autor, codigo e ano como "parâmetro" e as funções getNome, getCodigo e getAutor

class Livro {
private:
    string nome, autor, codigo;
    int ano;

public:
    Livro(string n, string a, string c, int an) {
        nome = n;
        autor = a;
        codigo = c;
        ano = an;
    }

    string getNome() { return nome; }
    string getAutor() { return autor; }
    string getCodigo() { return codigo; }
};

// Armazena as structs das listas encadeadas que guardam os alunos, livros e emprestimos alem de todas as funções logicas do sistema

class Sistema {
private:

    // Struct da lista encadeada aluno
    struct NoAluno { //Armazena um ponteiro pra uma instância da classe aluno e um ponteiro para o endereço da próxima struct NoAluno
        Aluno* aluno; 
        NoAluno* prox;
    };

    // -------- LIVROS --------
    struct NoLivro { //Armazena um ponteiro pra uma instância da classe livro e um ponteiro para o endereço da próxima struct NoLivro
        Livro* livro;
        NoLivro* prox;
    };

    // -------- EMPRESTIMOS --------
    struct NoEmprestimo {  //Armazena o número da matricula do aluno, o código do livro e um ponteiro para o endereço da próxima struct NoEmprestimo
        int matricula;
        string codigoLivro;
        NoEmprestimo* prox;
    };

    NoAluno* alunos;
    NoLivro* livros;
    NoEmprestimo* emprestimos;

public:
    Sistema() {  //Inicia os valores como null para serem o head  inicial das listas encadeadas, depois não são muito usados já que os valores são inseridos no começo da lista, pois fica mais bonito na apresentação
        alunos = nullptr; 
        livros = nullptr;
        emprestimos = nullptr;
    }

    // Validações pra fazer a inserção nas listas

    bool alunoExiste(int mat) {
        NoAluno* a = alunos;

        while (a != nullptr) {
            if (a->aluno->getMatricula() == mat)
                return true;
            a = a->prox;
        }
        return false;
    }

    bool livroExiste(string cod) {
        NoLivro* l = livros;

        while (l != nullptr) {
            if (l->livro->getCodigo() == cod)
                return true;
            l = l->prox;
        }
        return false;
    }

    // funções para inserir valores no inicio das listas ordenadas

    void cadastrarAluno() {
        string nome;
        int mat;

        cin.ignore();  //função pra evitar que o cin.getline ache que enter é caracter

        cout << "Nome: "; 
        getline(cin, nome); //função pra armazenar na variavel ate mesmo espaços em branco sem isso armazenar nomes ficaria estranho

        cout << "Matricula: ";
        cin >> mat;

        if (alunoExiste(mat)) {
            cout << "Erro: matricula ja cadastrada!\n";
            return;
        }

        Aluno* a = new Aluno(nome, mat);

        NoAluno* novo = new NoAluno;
        novo->aluno = a;
        novo->prox = alunos;
        alunos = novo;

        cout << "Aluno cadastrado!\n";
    }

    void cadastrarLivro() { 
        string nome, autor, cod;
        int ano;

        cin.ignore();

        cout << "Nome: ";
        getline(cin, nome);

        cout << "Autor: ";
        getline(cin, autor);

        cout << "Codigo: ";
        getline(cin, cod);

        cout << "Ano: ";
        cin >> ano;

        Livro* l = new Livro(nome, autor, cod, ano);

        NoLivro* novo = new NoLivro;
        novo->livro = l;
        novo->prox = livros;
        livros = novo;

        cout << "Livro cadastrado!\n";
    }

    void cadastrarEmprestimo() {
        try {
            int mat;
            string cod;

            cout << "Matricula: ";
            cin >> mat;

            cout << "Codigo livro: ";
            cin >> cod;

            if (!alunoExiste(mat))
                throw ErroSistema("Aluno nao encontrado!");

            if (!livroExiste(cod))
                throw ErroSistema("Livro nao encontrado!");

            NoEmprestimo* e = new NoEmprestimo;
            e->matricula = mat;
            e->codigoLivro = cod;
            e->prox = emprestimos;

            emprestimos = e;

            cout << "Emprestimo realizado!\n";
        }
        catch (ErroSistema e) {
            cout << "Erro: " << e.msg << endl;
        }
    }


    void cadastrarDevolucao() {
        int mat;
        string cod;

        cout << "Matricula: ";
        cin >> mat;

        cout << "Codigo: ";
        cin >> cod;

        NoEmprestimo* a = emprestimos;
        NoEmprestimo* ant = nullptr;

        while (a != nullptr) {
            if (a->matricula == mat && a->codigoLivro == cod) {

                if (ant == nullptr)
                    emprestimos = a->prox;
                else
                    ant->prox = a->prox;

                delete a;

                cout << "Devolucao realizada!\n";
                return;
            }

            ant = a;
            a = a->prox;
        }

        cout << "Emprestimo nao encontrado!\n";
    }


    void listarAlunos() {
        NoAluno* a = alunos;

        cout << "\nALUNOS:\n";

        while (a != nullptr) {
            cout << a->aluno->getNome()
                 << " | " << a->aluno->getMatricula() << endl; //percorrer cada nó e exibir seu valor, as funções getters são necessarias pois o programa armazena o ponteiro da instância da classe e não o dado em si
            a = a->prox;
        }
    }

    void listarLivros() {
        NoLivro* l = livros;

        cout << "\nACERVO:\n";

        while (l != nullptr) {
            cout << l->livro->getNome()
                 << " | " << l->livro->getCodigo() << endl;
            l = l->prox;
        }
    }

    void listarEmprestimos() {
        NoEmprestimo* e = emprestimos;

        cout << "\nEMPRESTIMOS:\n";

        while (e != nullptr) {
            cout << e->matricula
                 << " | " << e->codigoLivro << endl;
            e = e->prox;
        }
    }

    void listarEmprestimosAluno(int mat) {
        NoEmprestimo* e = emprestimos;

        cout << "\nSEUS EMPRESTIMOS:\n";

        while (e != nullptr) {
            if (e->matricula == mat)
                cout << e->codigoLivro << endl;
            e = e->prox;
        }
    }

    // funções pra gerar o menu

    void menuBibliotecaria() {
        int op;

        do {
            cout << "\n1-Cadastrar Aluno\n2-Cadastrar Livro\n3-Cadastrar Emprestimo\n4-Cadastrar Devolução\n5-Listar Acervo\n6-Listar Emprestimos\n7-listar Alunos\n0-Voltar\nOpc: ";
            cin >> op;

            switch (op) {
                case 1: cadastrarAluno(); break;
                case 2: cadastrarLivro(); break;
                case 3: cadastrarEmprestimo(); break;
                case 4: cadastrarDevolucao(); break;
                case 5: listarLivros(); break;
                case 6: listarEmprestimos(); break;
                case 7: listarAlunos(); break;
            }

        } while (op != 0);
    }

    void menuAluno() {
        int mat;

        cout << "Matricula: ";
        cin >> mat;

        if (!alunoExiste(mat)) {
            cout << "Aluno nao encontrado!\n";
            return;
        }

        int op;

        do {
            cout << "\n1-Ver Acervo\n2- Listar Meus Emprestimos\n0-Voltar\nOpc: ";
            cin >> op;

            switch (op) {
                case 1: listarLivros(); break;
                case 2: listarEmprestimosAluno(mat); break;
            }

        } while (op != 0);
    }

    // Destrutores das classes pra não ficar com dados perdidos na heap após a execução

    ~Sistema() {
        NoAluno* a;
        while (alunos) {
            a = alunos;
            alunos = alunos->prox;
            delete a->aluno;
            delete a;
        }

        NoLivro* l;
        while (livros) {
            l = livros;
            livros = livros->prox;
            delete l->livro;
            delete l;
        }

        NoEmprestimo* e;
        while (emprestimos) {
            e = emprestimos;
            emprestimos = emprestimos->prox;
            delete e;
        }
    }
};

// função main

int main() {
    Sistema s;

    int op;

    do {
        cout << "\n1-Aluno\n2-Bibliotecaria\n0-Sair\nOpc: ";
        cin >> op;

        if (op == 1) s.menuAluno();
        if (op == 2) s.menuBibliotecaria();

    } while (op != 0);

    return 0;
}

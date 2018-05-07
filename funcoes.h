#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

//Gonçalo Rodrigues e João Castilho
typedef struct data
{
    int dia,ano,mes;
    int horas,minutos;

}Data;

typedef struct paciente
{
    char nome[200];
    int BI,pulseira;
    Data data;
}Pessoa;

typedef struct lnode * List;
typedef struct lnode{
    Pessoa info;
    List next;
} List_node;
typedef struct lnode * List2;
typedef struct lnode2{
    Pessoa *info;
    List next;
} List_node2;

List cria_lista();
List cria_lista2();
Pessoa inserir_dados();
void insere_lista(List lista,Pessoa paciente);
void insere_pulseira(List triagem,List verde, List laranja,List vermelho,List2 global,FILE * ftriagem,FILE * fverde, FILE * flaranja, FILE * fvermelho, FILE * fglobal);
Pessoa procura_paciente(int bi,List lista);
void imprime_todos(List lista);
void imprime_global(List2 lista);
void imprime_paciente(Pessoa paciente);
void procura_na_lista (List lista,int bi, List *ant, List *atual);
void procura_global (List2 lista,int bi, List2 *ant, List2 *atual);
void elimina_paciente (List lista,int bi);
void elimina_paciente_global(List2 lista,int bi);
void insere_global(List lista,Pessoa * paciente);
int lista_vazia(List lista);
int global_vazia(List2 lista);
Pessoa procura_principio (List lista);
void chamar_consulta(List vermelho, List laranja, List verde, List2 global,int *red,int *orange,FILE * fverde,FILE * flaranja,FILE * fvermelho,FILE *fglobal);
void recebe_ficheiros(FILE * flista,List lista);
void triagem_ficheiros(FILE * ftriagem,List triagem);
void vermelho_ficheiros(FILE * fvermelho,List vermelho);
void laranja_ficheiros(FILE * flaranja,List laranja);
void verde_ficheiros(FILE * fverde,List verde);
void global_ficheiros(FILE * fglobal,List2 global);
void seguranca_data(Pessoa * paciente);
void seguranca_horas(Pessoa * paciente);
void recebe_contador(FILE * flista,int * red,int * orange);
void atualiza_contador(FILE * fcontadores,int red,int orange);
#endif // FUNCOES_H_INCLUDED

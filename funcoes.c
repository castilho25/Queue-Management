#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//Gonçalo Rodrigues e João Castilho
List cria_lista(){
    List aux;
    aux=(List)malloc(sizeof(List_node));
    Pessoa nulo;
    if (aux!= NULL)
    {
        aux->info=nulo;
        aux->next=NULL;
    }
    return aux;
}
List cria_lista2(){
    List2 aux;
    aux=(List)malloc(sizeof(List_node));
    Pessoa nulo;
    if (aux!= NULL)
    {
        aux->info=nulo;
        aux->next=NULL;
    }
    return aux;
}

Pessoa inserir_dados()
{
    int num,x;
    Pessoa paciente;
    printf("Nome: ");
    getchar();
    fgets(paciente.nome,100,stdin);
    while (strcmp(paciente.nome,"\n")==0){
        printf("Insira outra vez o nome: ");
        fgets(paciente.nome,100,stdin);
    }
    printf("BI: ");
    scanf("%d",&paciente.BI);
    fflush(stdin);
    while (paciente.BI>99999999|| paciente.BI <1000000){
        printf("Numero invalido!\n");
        printf("BI: ");
        scanf("%d",&paciente.BI);
        fflush(stdin);
    }

    printf("Data de entrada(dd/mm/aaaa): ");
    scanf("%d/%d/%d/",&paciente.data.dia,&paciente.data.mes,&paciente.data.ano);
    fflush(stdin);
    seguranca_data(&paciente);
    printf("Hora de entrada(hh:mm): ");
    scanf("%d:%d",&paciente.data.horas,&paciente.data.minutos);
    fflush(stdin);
    seguranca_horas(&paciente);
    return paciente;

}

void insere_lista(List lista,Pessoa paciente)
{
    List ptr = lista;
    List no;
    no=(List)malloc(sizeof(List_node));
    while(ptr->next !=NULL)
        ptr=ptr->next;
    no->info=paciente;
    ptr->next = no;
    no->next=NULL;
}
void insere_global(List2 lista,Pessoa * paciente)
{
    List ptr = lista;
    List no;
    no=(List)malloc(sizeof(List_node));
    while(ptr->next !=NULL)
        ptr=ptr->next;
    no->info=*paciente;
    ptr->next = no;
    no->next=NULL;
}

void insere_pulseira(List triagem,List verde, List laranja,List vermelho,List2 global,FILE * ftriagem,FILE * fverde, FILE * flaranja, FILE * fvermelho, FILE * fglobal){
    int bi;
    Pessoa paciente;
    printf("BI: ");
    scanf("%d",&bi);
    fflush(stdin);
    while (bi>99999999 && bi<=1000000){
        printf("Número inválido!!");
        printf("BI: ");
        scanf("%d",&bi);
        fflush(stdin);
    }
    paciente = procura_paciente(bi,triagem);
    if (strcmp(paciente.nome,"")!=0){
        printf("%s",paciente.nome);
        printf("1) Pulseira Verde\n2) Pulseira Laranja\n3) Pulseira Vermelho\nNumero: ");
        scanf("%d",&paciente.pulseira);
        if (paciente.pulseira== 1){
            insere_lista(verde,paciente);
            elimina_paciente(triagem,bi);
            insere_global(global,&paciente);
            verde_ficheiros(fverde,verde);
            triagem_ficheiros(ftriagem,triagem);
            global_ficheiros(fglobal,global);
        }
        else if (paciente.pulseira == 2){
            insere_lista(laranja,paciente);
            elimina_paciente(triagem,bi);
            insere_global(global,&paciente);
            laranja_ficheiros(flaranja,laranja);
            triagem_ficheiros(ftriagem,triagem);
            global_ficheiros(fglobal,global);
        }
        else if (paciente.pulseira == 3){
            insere_lista(vermelho,paciente);
            elimina_paciente(triagem,bi);
            insere_global(global,&paciente);
            vermelho_ficheiros(fvermelho,vermelho);
            triagem_ficheiros(ftriagem,triagem);
            global_ficheiros(fglobal,global);
        }
        else
            printf("Numero errado!");
    }
}

Pessoa procura_paciente(int bi,List lista){
    List atual=lista->next;
    Pessoa ptr;
    while (atual != NULL){
        ptr=atual->info;
        if (bi==ptr.BI){
            return ptr;
            break;
        }
        atual = atual->next;
    }
    if (atual == NULL){
        printf("Elemento não encontrado!");
    }
}
void imprime_paciente(Pessoa paciente){
    printf("Nome: %s\n",paciente.nome);
    printf("BI: %d\n",paciente.BI);
    printf("Hora de entrada: %d/%d/%d -  %d:",paciente.data.dia,paciente.data.mes,paciente.data.ano,paciente.data.horas);
    if(paciente.data.minutos<10)
        printf("0%d\n",paciente.data.minutos);
    else
        printf("%d\n",paciente.data.minutos);
}
void imprime_todos(List lista){
    List ptr=lista->next;
    int num=1;
    while (ptr !=NULL)
    {
        printf("\nPaciente %d\n",num);
        imprime_paciente(ptr->info);
        printf("_____________________________________________________________________\n");
        ptr=ptr->next;
        num++;
    }
}
void imprime_global(List2 lista){
    List2 ptr=lista->next;
    int num=1;
    while (ptr !=NULL)
    {
        printf("\nPaciente %d\n",num);
        imprime_paciente(ptr->info);
        printf("_____________________________________________________________________\n");
        ptr=ptr->next;
        num++;
    }
}

void procura_na_lista (List lista,int bi, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    Pessoa ptr;
    while (*atual != NULL){
        ptr=(*atual)->info;
        if (bi == ptr.BI)
            break;
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if (*atual == NULL )
        printf("Elemento não encontrado");
}
void procura_global (List2 lista,int bi, List2 *ant, List2 *atual){
    *ant = lista; *atual = lista->next;
    Pessoa ptr;
    while (*atual != NULL){
        ptr=(*atual)->info;
        if (bi == ptr.BI)
            break;
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if (*atual == NULL )
        printf("Elemento não encontrado");
}
void elimina_paciente (List lista,int bi){
    List ant,atual;
    procura_na_lista(lista,bi,&ant,&atual);
    if (atual != NULL) {
        ant->next = atual->next;
        free (atual);
    }
}
void elimina_paciente_global(List2 lista,int bi){
    List2 ant,atual;
    procura_global(lista,bi,&ant,&atual);
    if (atual != NULL) {
        ant->next = atual->next;
        free (atual);
    }
}

int lista_vazia(List lista) {
    return (lista->next == NULL ? 1 : 0);
}
int global_vazia(List2 lista) {
    return (lista->next == NULL ? 1 : 0);
}
Pessoa procura_principio (List lista){
    Pessoa paciente;
    paciente = (lista->next)->info;
    return paciente;
}

void chamar_consulta(List vermelho, List laranja, List verde, List2 global,int *red,int *orange,FILE * fverde,FILE * flaranja,FILE * fvermelho,FILE *fglobal){
    Pessoa paciente;
    if(lista_vazia(global)==1)
        printf("Não está ninguém em espera para consulta.");
    else{
        printf("\t\tPróximo paciente\n");
        printf("_____________________________________________________________________\n");
        if ((*red)<3){
            if (lista_vazia(vermelho)==0){
                paciente = procura_principio(vermelho);
                printf("Prioridade: Vermelho\n");
                imprime_paciente(paciente);
                elimina_paciente(vermelho,paciente.BI);
                elimina_paciente_global(global,paciente.BI);
                vermelho_ficheiros(fvermelho,vermelho);
                global_ficheiros(fglobal,global);
                (*red)++;
            }
            else if (lista_vazia(vermelho)==1){
                if (lista_vazia(laranja)==0){
                    paciente = procura_principio(laranja);
                    printf("Prioridade: Laranja\n");
                    imprime_paciente(paciente);
                    elimina_paciente(laranja,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    laranja_ficheiros(flaranja,laranja);
                    global_ficheiros(fglobal,global);
                    (*orange)++;
                    (*red)=0;
                }
                else if (lista_vazia(verde)==0){
                    paciente = procura_principio(verde);
                    printf("Prioridade: Verde\n");
                    imprime_paciente(paciente);
                    elimina_paciente(verde,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    verde_ficheiros(fverde,verde);
                    global_ficheiros(fglobal,global);
                    (*orange)=0;
                    (*red)=0;
                }
                else
                    printf("Não está ninguém em lista de espera para consulta!");
            }
        }
        else if ((*orange)<5){
            if (lista_vazia(laranja)==0){
                paciente = procura_principio(laranja);
                printf("Prioridade: Laranja\n");
                imprime_paciente(paciente);
                elimina_paciente(laranja,paciente.BI);
                elimina_paciente_global(global,paciente.BI);
                laranja_ficheiros(flaranja,laranja);
                global_ficheiros(fglobal,global);
                (*orange)++;
                (*red)=0;
            }
            else if (lista_vazia(laranja)==1){
                if (lista_vazia(verde)==0){
                    paciente = procura_principio(verde);
                    printf("Prioridade: Verde\n");
                    imprime_paciente(paciente);
                    elimina_paciente(verde,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    verde_ficheiros(fverde,verde);
                    global_ficheiros(fglobal,global);
                    (*orange)=0;
                    (*red)=0;
                }
                else if (lista_vazia(vermelho)==0){
                    paciente = procura_principio(vermelho);
                    printf("Prioridade: Vermelho\n");
                    imprime_paciente(paciente);
                    elimina_paciente(vermelho,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    vermelho_ficheiros(fvermelho,vermelho);
                    global_ficheiros(fglobal,global);
                    (*red)++;
                    (*orange)=0;
                }
                else
                    printf("Não está ninguém em lista de espera para consulta!");
            }
        }
        else{
            if (lista_vazia(verde)==0){
                paciente = procura_principio(verde);
                printf("Prioridade: Verde\n");
                imprime_paciente(paciente);
                elimina_paciente(verde,paciente.BI);
                elimina_paciente_global(global,paciente.BI);
                verde_ficheiros(fverde,verde);
                global_ficheiros(fglobal,global);
                (*red)=0;
                (*orange)=0;
            }
            else if (lista_vazia(verde)==1){
                if (lista_vazia(vermelho)==0){
                    paciente = procura_principio(vermelho);
                    printf("Prioridade: Vermelho\n");
                    imprime_paciente(paciente);
                    elimina_paciente(vermelho,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    vermelho_ficheiros(fvermelho,vermelho);
                    global_ficheiros(fglobal,global);
                    (*red)++;
                    (*orange)=0;
                }
                else if (lista_vazia(laranja)==0){
                    paciente = procura_principio(laranja);
                    printf("Prioridade: Laranja\n");
                    imprime_paciente(paciente);
                    elimina_paciente(laranja,paciente.BI);
                    elimina_paciente_global(global,paciente.BI);
                    laranja_ficheiros(flaranja,laranja);
                    global_ficheiros(fglobal,global);
                    (*orange)++;
                    (*red)=0;
                }
            }
        }
    }
}
void recebe_contador(FILE * flista,int *red,int *orange){
    fscanf(flista,"%d,%d",red,orange);
}
void recebe_ficheiros(FILE * flista,List lista){
    Pessoa dados;
    while (fgets(dados.nome,40,flista) != NULL){
        fscanf(flista,"%d,%d/%d/%d,%d:%d",&dados.BI,&dados.data.dia,&dados.data.mes,&dados.data.ano,&dados.data.horas,&dados.data.minutos);
        insere_lista(lista,dados);
    }
}
void triagem_ficheiros(FILE * ftriagem,List triagem){
    ftriagem = fopen("triagem.txt","w");
    List atual=triagem->next;
    Pessoa dados;
    while(atual!=NULL)
    {
        dados=atual->info;
        fprintf(ftriagem,"%s%d,%d/%d/%d,%d:%d",dados.nome,dados.BI,dados.data.dia,dados.data.mes,dados.data.ano,dados.data.horas,dados.data.minutos);
        atual=atual->next;
    }
    fclose(ftriagem);
}
void vermelho_ficheiros(FILE * fvermelho,List vermelho){
    fvermelho = fopen("vermelho.txt","w");
    List atual=vermelho->next;
    Pessoa dados;
    while(atual!=NULL)
    {
        dados=atual->info;
        fprintf(fvermelho,"%s%d,%d/%d/%d,%d:%d",dados.nome,dados.BI,dados.data.dia,dados.data.mes,dados.data.ano,dados.data.horas,dados.data.minutos);
        atual=atual->next;
    }
    fclose(fvermelho);
}
void laranja_ficheiros(FILE * flaranja,List laranja){
    flaranja = fopen("laranja.txt","w");
    List atual=laranja->next;
    Pessoa dados;
    while(atual!=NULL)
    {
        dados=atual->info;
        fprintf(flaranja,"%s%d,%d/%d/%d,%d:%d",dados.nome,dados.BI,dados.data.dia,dados.data.mes,dados.data.ano,dados.data.horas,dados.data.minutos);
        atual=atual->next;
    }
    fclose(flaranja);
}
void verde_ficheiros(FILE * fverde,List verde){
    fverde = fopen("verde.txt","w");
    List atual=verde->next;
    Pessoa dados;
    while(atual!=NULL)
    {
        dados=atual->info;
        fprintf(fverde,"%s%d,%d/%d/%d,%d:%d",dados.nome,dados.BI,dados.data.dia,dados.data.mes,dados.data.ano,dados.data.horas,dados.data.minutos);
        atual=atual->next;
    }
    fclose(fverde);
}
void global_ficheiros(FILE * fglobal,List2 global){
    fglobal = fopen("global.txt","w");
    List atual=global->next;
    Pessoa dados;
    while(atual!=NULL)
    {
        dados=atual->info;
        fprintf(fglobal,"%s%d,%d/%d/%d,%d:%d",dados.nome,dados.BI,dados.data.dia,dados.data.mes,dados.data.ano,dados.data.horas,dados.data.minutos);
        atual=atual->next;
    }
    fclose(fglobal);
}
void seguranca_data(Pessoa * paciente){
    int dia=(*paciente).data.dia,mes=(*paciente).data.mes,ano=(*paciente).data.ano;
    while(((dia>31 || dia<1 || ano<2014||ano>2999) && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12))||((dia>30 || dia<1 || ano<2014|| ano>2999) && (mes==4 || mes==6 || mes==9 || mes==11))||((dia>29 || dia<1 || ano<2014|| ano>2999) && mes==2)||(mes>12 || mes<1)){
        printf("Data invalida!\nData de entrada (dd/mm/aaaa): ");
        scanf("%d/%d/%d",&dia,&mes,&ano);
    }
    (*paciente).data.dia=dia;
    (*paciente).data.mes=mes;
    (*paciente).data.ano=ano;
}
void seguranca_horas(Pessoa * paciente){
    while((*paciente).data.horas>23 || (*paciente).data.minutos>59||(*paciente).data.horas<01||(*paciente).data.minutos<00){
        printf("Hora de entrada invávida!\nHora de entrada (hh:mm): ");
        scanf("%d:%d",&(*paciente).data.horas,&(*paciente).data.minutos);
        }
}
void atualiza_contador(FILE * fcontadores,int red,int orange){
    fcontadores = fopen("contador.txt","w");
    fprintf(fcontadores,"%d,%d",red,orange);
    fclose(fcontadores);
}

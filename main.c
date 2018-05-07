#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
//Gonçalo Rodrigues e João Castilho
int main()
{
        FILE *ftriagem,*fvermelho,*fverde,*flaranja,*fglobal,*fcontadores;
        int i=0,num,bi,pulseira,red=0,orange=0;
        List triagem,vermelho,laranja,verde;
        List2 global;
        Pessoa paciente;
        triagem = cria_lista();
        vermelho = cria_lista();
        laranja = cria_lista();
        verde = cria_lista();
        global = cria_lista2();
        ftriagem = fopen("triagem.txt","r");
        recebe_ficheiros(ftriagem,triagem);
        fclose(ftriagem);
        fvermelho = fopen("vermelho.txt","r");
        recebe_ficheiros(fvermelho,vermelho);
        fclose(fvermelho);
        fverde=fopen("verde.txt","r");
        recebe_ficheiros(fverde,verde);
        fclose(fverde);
        flaranja=fopen("laranja.txt","r");
        recebe_ficheiros(flaranja,laranja);
        fclose(flaranja);
        fglobal=fopen("global.txt","r");
        recebe_ficheiros(fglobal,global);
        fclose(fglobal);
        fcontadores=fopen("contador.txt","r");
        recebe_contador(fcontadores,&red,&orange);
        fclose(fcontadores);
        do{
            printf("\n\t1) Inserir paciente na fila de espera da Triagem\n\t2) Inserir pulseira do paciente\n\t3) Ver fila de espera na Triagem\n\t4) Ver fila de espera na prioridade vermelha\n");
            printf("\t5) Ver fila de espera na prioridade laranja \n\t6) Ver fila de espera na prioridade verde \n\t7) Ver lista global\n\t8) Eliminar paciente da fila de espera da Triagem\n");
            printf("\t9) Eliminar paciente em espera para consulta\n\t10) Chamar para a consulta\n\n\t0) Sair\n\tInserir numero: ");
            scanf("%d",&num);
            if (num==1){
                paciente = inserir_dados();
                insere_lista(triagem,paciente);
                triagem_ficheiros(ftriagem,triagem);
            }
            else if (num==2){
                if (lista_vazia(triagem)==1)
                    printf("Não está ninguém em espera para triagem!");
                else
                    insere_pulseira(triagem,verde,laranja,vermelho,global,ftriagem,fverde,flaranja,fvermelho,fglobal);

            }
            else if (num==3){
                imprime_todos(triagem);
            }
            else if (num==4)
                imprime_todos(vermelho);
            else if (num==5)
                imprime_todos(laranja);
            else if (num==6)
                imprime_todos(verde);
            else if (num==7)
                imprime_global(global);
            else if (num==8){
                if (lista_vazia(triagem)==1)
                    printf("Não está ninguém em espera para triagem!");
                else{
                    printf("BI: ");
                    scanf("%d",&bi);
                    if (bi>99999999 && bi<=1000000)
                        printf("Número inválido!!");
                    else{
                        elimina_paciente(triagem,bi);
                        triagem_ficheiros(ftriagem,triagem);
                        printf("Paciente eliminado!");
                    }
                }
            }
            else if (num==9){
                if (global_vazia(global)==1)
                    printf("Não está ninguém em espera para consulta!");
                else{
                    printf("1) Pulseira Verde\n2) Pulseira Laranja\n3) Pulseira Vermelho\nNumero: ");
                    scanf("%d",&pulseira);
                    printf("BI: ");
                    scanf("%d",&bi);
                    if (bi>99999999 && bi<=1000000)
                        printf("Número inválido!!");
                    else{
                        if (pulseira==1){
                            elimina_paciente(verde,bi);
                            elimina_paciente(global,bi);
                            verde_ficheiros(fverde,verde);
                            global_ficheiros(fglobal,global);
                        }
                        else if (pulseira==2){
                            elimina_paciente(global,bi);
                            elimina_paciente(laranja,bi);
                            laranja_ficheiros(flaranja,laranja);
                            global_ficheiros(fglobal,global);
                        }
                        else if (pulseira==3){
                            elimina_paciente(global,bi);
                            elimina_paciente(vermelho,bi);
                            vermelho_ficheiros(fvermelho,vermelho);
                            global_ficheiros(fglobal,global);
                        }
                        else
                            printf("Prioridade invalida!");
                    }
                }
            }
            else if (num==10){
                chamar_consulta(vermelho,laranja,verde,global,&red,&orange,fverde,flaranja,fvermelho,fglobal);
                atualiza_contador(fcontadores,red,orange);
            }
            else if(num==0){
                break;
            }
            else
                printf("Dados inválidos! Repita de novo o processo!");
        }while (num!=0);
    return 0;
}

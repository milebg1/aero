#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct sldisp {                                                            
    struct sldisp *prox;                                                
    char codigo[6];                                                      
    int contadorDecolagem;                                              
    int contadorAterrissagem;                                            
}; typedef struct sldisp SLDISP;                                        

struct ldisp {                                                            
    struct ldisp *prox;                                                  
    struct sldisp *com;                                                  
    char letra;                                                          
}; typedef struct ldisp LDISP;           

struct fdec {
	struct fdec *prox;
	char codigo[6];
}; typedef struct fdec FDEC;

struct relat {
    struct relat * prox;
    char codigo[6];
    char oper[12];
    time_t horario;
}; typedef struct relat RELAT;

struct header {
	struct relat *iniciorelat;
	struct ldisp *inicioldisp;
	struct fdec *iniciofdec;
	struct fdec *iniciofate;
}; typedef struct header HEADER;

void insereLDISP(struct header **inicio) {                                    
    char cod[6];                                                          
    printf("Digite o codigo do aviao a ser adicionado a LDISP: ");        
    fgets(cod, sizeof(cod), stdin);                                      
    getchar();      
    
    struct ldisp *aux_verifica = (*inicio)->inicioldisp;
    while (aux_verifica != NULL) {
        if (aux_verifica->com != NULL && strcmp(aux_verifica->com->codigo, cod) == 0) {
            printf("O codigo ja foi cadastrado anteriormente.\n");
            return;
        }
        aux_verifica = aux_verifica->prox;
    }
    
    struct sldisp *snovo = (struct sldisp*)malloc(sizeof(SLDISP));        
    if (snovo == NULL) {                                                  
        printf("Erro ao alocar memoria.\n");                              
        exit(1);                                                          
    }                                                                      
    
    strcpy(snovo->codigo, cod);                                           
    snovo->contadorAterrissagem = 0;                                       
    snovo->contadorDecolagem = 0;                                         
    snovo->prox = NULL;                                                    
  
    if (((*inicio)->inicioldisp) == NULL) {                                                    
        ((*inicio)->inicioldisp)= (struct ldisp*)malloc(sizeof(LDISP));                     
        ((*inicio)->inicioldisp->com) = snovo;                                               
        ((*inicio)->inicioldisp->letra) = cod[0];                                            
        ((*inicio)->inicioldisp->prox) = NULL;  
        printf("Aviao cadastrado em LDISP.\n");  
        return;                                                            
    }                                                                      
    
    struct ldisp *aux = (*inicio)->inicioldisp;                                              
    while (aux != NULL) {                                                   
        if (aux->letra == cod[0]) {                                        
            snovo->prox = aux->com;                                        
            aux->com = snovo;
            printf("Aviao cadastrado em LDISP.\n");  
            return;                                                       
        }                                                                  
        aux = aux->prox;                                                   
    }                                                                      
    
    struct ldisp *lnovo = (struct ldisp*)malloc(sizeof(LDISP));            
    lnovo->prox = (*inicio)->inicioldisp;                                                    
    lnovo->letra = cod[0];                                                 
    lnovo->com = snovo;                                                     
    (*inicio)->inicioldisp = lnovo;       
	
	printf("Aviao cadastrado em LDISP.\n");                                                  
}

void insereFDEC(struct header **inicio) {
    struct fdec *dnovo;
    struct ldisp *aux;
    struct sldisp *aux2;
    struct fdec *aux3;
    
    char cod[6];                                                          
    printf("Digite o codigo do aviao a ser adicionado a FDEC: ");        
    fgets(cod, sizeof(cod), stdin);                                      
    getchar();                                                             
    
    // Verifica se o avião está em LDISP
    aux = (*inicio)->inicioldisp;
    while (aux != NULL) {
        if (aux->letra == cod[0]) {
            aux2 = aux->com;
            while (aux2 != NULL) {
                if (strcmp(aux2->codigo, cod) == 0) {
                    printf("O aviao esta em LDISP, continuando com a solicitacao.\n");
                    break;
                } else {
                    aux2 = aux2->prox;
                }
            }
            if (aux2 != NULL) {
                break; // Avião encontrado em LDISP
            }
        }
        aux = aux->prox;
    }

    // Se o avião não foi encontrado em LDISP, encerra a função
    if (aux2 == NULL) {
        printf("O aviao nao pode ser adicionado em FDEC pois nao esta em LDISP.\n\n");
        return;
    }

    // Verifica se o avião está em FATE
    aux3 = (*inicio)->iniciofate;
    while (aux3 != NULL) {
        if (strcmp(aux3->codigo, cod) == 0) {
            printf("O aviao nao pode ser adicionado a FDEC pois esta em FATE.\n\n");
            return;
        }
        aux3 = aux3->prox;
    }
    
    // Se chegou aqui, o avião está em LDISP e não está em FATE
    // Então pode ser adicionado em FDEC
    dnovo = (struct fdec*)malloc(sizeof(struct fdec));
    if (dnovo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    strcpy(dnovo->codigo, cod); 
    dnovo->prox = (*inicio)->iniciofdec;
    (*inicio)->iniciofdec = dnovo;
    
    printf("Cadastro em FDEC confirmado.\n\n");
}


void insereFATE(struct header **inicio) {
    struct fdec *anovo;
    struct ldisp *aux;
    struct sldisp *aux2;
    struct fdec *aux3;
    
    char cod[6];                                                          
    printf("Digite o codigo do aviao a ser adicionado a FATE: ");        
    fgets(cod, sizeof(cod), stdin);                                      
    getchar();                                                             
    
    // Verifica se o avião está em LDISP
    aux = (*inicio)->inicioldisp;
    while (aux != NULL) {
        if (aux->letra == cod[0]) {
            aux2 = aux->com;
            while (aux2 != NULL) {
                if (strcmp(aux2->codigo, cod) == 0) {
                    printf("O aviao esta em LDISP, continuando com a solicitacao.\n");
                    break;
                } else {
                    aux2 = aux2->prox;
                }
            }
            if (aux2 != NULL) {
                break; // Avião encontrado em LDISP
            }
        }
        aux = aux->prox;
    }

    // Se o avião não foi encontrado em LDISP, encerra a função
    if (aux2 == NULL) {
        printf("O aviao nao pode ser adicionado em FATE pois nao esta em LDISP.\n\n");
        return;
    }

    // Verifica se o avião está em FDEC
    aux3 = (*inicio)->iniciofdec;
    while (aux3 != NULL) {
        if (strcmp(aux3->codigo, cod) == 0) {
            printf("O aviao nao pode ser adicionado a FATE pois esta em FDEC.\n\n");
            return;
        }
        aux3 = aux3->prox;
    }
    
    // Se chegou aqui, o avião está em LDISP e não está em FDEC
    // Então pode ser adicionado em FATE
    anovo = (struct fdec*)malloc(sizeof(struct fdec));
    if (anovo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    strcpy(anovo->codigo, cod); 
    anovo->prox = (*inicio)->iniciofate;
    (*inicio)->iniciofate = anovo;
    
    printf("Cadastro em FATE confirmado.\n");
}


void removeFDEC (struct header **inicio) {
    if ((*inicio)->iniciofdec == NULL) {
        printf("FDEC esta vazia.\n");
        return;
    }
    
    struct fdec *aux = (*inicio)->iniciofdec;
    struct fdec *ant = NULL;
    struct relat *rnovo = NULL;
    rnovo=(struct relat*)malloc(sizeof(RELAT));
    
    while (aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
    }
    
    struct ldisp *aux1 = (*inicio)->inicioldisp;
    struct sldisp *aux2 = NULL;
    while (aux1 != NULL) {
        aux2 = aux1->com;
        while (aux2 != NULL) {
            if (strcmp(aux2->codigo, aux->codigo) == 0) {
                aux2->contadorDecolagem++;
                rnovo->horario = time(NULL);
                break;
            }
            aux2 = aux2->prox;
        }
        if (aux2 != NULL) break;
        aux1 = aux1->prox;
    }
    strcpy(rnovo->oper, "Decolagem");
    if (ant == NULL) {
        strcpy(rnovo->codigo, ((*inicio)->iniciofdec)->codigo);
        free((*inicio)->iniciofdec);
        (*inicio)->iniciofdec = NULL;
    } else {
        strcpy(rnovo->codigo, ant->prox->codigo);
        ant->prox = NULL;
        free(aux);
    }
    
    rnovo->prox=NULL;
    if((*inicio)->iniciorelat == NULL){
        (*inicio)->iniciorelat = rnovo;
    }
    else{
        rnovo->prox=(*inicio)->iniciorelat;
	    (*inicio)->iniciorelat=rnovo;
  }
  printf("O aviao %s esta autorizado a decolar.\n", rnovo->codigo);
  printf("O aviao %s decolou.\n", rnovo->codigo);
}

void removeFATE(struct header **inicio) {
    if ((*inicio)->iniciofate == NULL) {
        printf("FATE esta vazia.\n\n");
        return;
    }
    
    struct fdec *aux = (*inicio)->iniciofate;
    struct fdec *ant = NULL;
    struct relat *rnovo = NULL;
    rnovo=(struct relat*)malloc(sizeof(RELAT));
    
    while (aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
    }
    
    struct ldisp *aux1 = (*inicio)->inicioldisp;
    struct sldisp *aux2 = NULL;
    while (aux1 != NULL) {
        aux2 = aux1->com;
        while (aux2 != NULL) {
            if (strcmp(aux2->codigo, aux->codigo) == 0) {
                aux2->contadorAterrissagem++;
                rnovo->horario = time(NULL);
                break;
            }
            aux2 = aux2->prox;
        }
        if (aux2 != NULL) break;
        aux1 = aux1->prox;
    }
    strcpy(rnovo->oper, "Aterrissagem");
    if (ant == NULL) {
        strcpy(rnovo->codigo, ((*inicio)->iniciofate)->codigo);
        free((*inicio)->iniciofate);
        (*inicio)->iniciofate = NULL;
    } else {
        strcpy(rnovo->codigo, ant->prox->codigo);
        ant->prox = NULL;
        free(aux);
    }
    
    rnovo->prox=NULL;
    if((*inicio)->iniciorelat == NULL){
        (*inicio)->iniciorelat = rnovo;
    }
    else{
        rnovo->prox=(*inicio)->iniciorelat;
	    (*inicio)->iniciorelat=rnovo;
  }
  printf("O aviao %s esta autorizado a aterrissar.\n", rnovo->codigo);
  printf("O aviao %s aterrissou.\n", rnovo->codigo);
}

void escreveLDISP(struct header **inicio) {
    char a[2];
    printf("Digite a letra inicial dos avioes que deseja verificar: ");
    fgets(a, sizeof(a), stdin);
    getchar();
    
    struct ldisp *aux = (*inicio)->inicioldisp;
    while (aux != NULL && aux->letra != a[0]) {
        aux = aux->prox;
    }
    
    if (aux == NULL) {
        printf("Nao ha avioes com a letra inicial '%c'.\n\n", a[0]);
        fflush(stdout);
        setbuf(stdin, NULL);
        return;
    }
    
    struct sldisp *aux2 = aux->com;
    while (aux2 != NULL) {
        printf("\nAviao: %s\n", aux2->codigo);
        printf("Decolagens: %d\n", aux2->contadorDecolagem);
        printf("Aterrissagens: %d\n", aux2->contadorAterrissagem);
        aux2 = aux2->prox;
    }
}

void escreveRELAT(struct header **inicio) {
    if ((*inicio)->iniciorelat == NULL) {
        printf("Lista de relatorios vazia.\n");
        return;
    }

    printf("Lista de relatorios:\n");
    struct relat *aux = (*inicio)->iniciorelat;
    while (aux != NULL) {
        printf("Codigo do aviao: %s\n", aux->codigo);
        printf("Operacao: %s\n", aux->oper);
        printf("Horario: %s", ctime(&aux->horario));
        printf("\n\n");
        aux = aux->prox;
    }
}

void removeLDISP(struct header **inicio) {
    
    if ((*inicio)->inicioldisp == NULL) {
        printf("Lista de avioes vazia.\n");
        return;
    }
    
    char cod[6];                                                          
    printf("Digite o codigo do aviao a ser removido de LDISP: ");        
    fgets(cod, sizeof(cod), stdin);                                      
    getchar();  

    struct ldisp *anterior = NULL;
    struct ldisp *atual = (*inicio)->inicioldisp;

    while (atual != NULL) {
        struct sldisp *aux = atual->com;
        struct sldisp *anterior_sldisp = NULL;

        while (aux != NULL) {
            if (strcmp(aux->codigo, cod) == 0) {
                if (anterior_sldisp == NULL) {
                    atual->com = aux->prox;
                } else {
                    anterior_sldisp->prox = aux->prox;
                }
                free(aux);
                printf("Aviao removido de LDISP.\n");
                return;
            }
            anterior_sldisp = aux;
            aux = aux->prox;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Aviao nao encontrado em LDISP.\n");
}
void proximas_decolagens(struct header **inicio) {
    if ((*inicio)->iniciofdec == NULL) {
        printf("Lista de decolagens vazia.\n");
        return;
    }

    printf("Proximas decolagens previstas:\n");
    struct fdec *aux = (*inicio)->iniciofdec;
    while (aux != NULL) {
        printf("%s\n", aux->codigo);
        aux = aux->prox;
    }
}

void proximas_aterrissagens(struct header **inicio) {
    if ((*inicio)->iniciofate == NULL) {
        printf("Lista de aterrissagens vazia.\n");
        return;
    }

    printf("Proximas aterrissagens previstas:\n");
    struct fdec *aux = (*inicio)->iniciofate;
    while (aux != NULL) {
        printf("%s\n", aux->codigo);
        aux = aux->prox;
    }
}

void quantidade_voos(struct header **inicio) {
    int decolagens = 0;
    int aterrisagens = 0;

    struct ldisp *aux = (*inicio)->inicioldisp;
    while (aux != NULL) {
        struct sldisp *aux2 = aux->com;
        while (aux2 != NULL) {
            decolagens += aux2->contadorDecolagem;
            aterrisagens += aux2->contadorAterrissagem;
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }

    printf("Quantidade de voos:\n");
    printf("Decolagens: %d\n", decolagens);
    printf("Aterrisagens: %d\n", aterrisagens);
}


int main() {

	struct header *inicio = (struct header*)malloc(sizeof(HEADER));        
    if (inicio == NULL) {                                                  
        printf("Erro ao alocar memoria.\n");                              
        exit(1);    
	}
	
	inicio->iniciofate = NULL;
	inicio->iniciofdec = NULL;
	inicio->inicioldisp = NULL;
	inicio->iniciorelat = NULL;
	
    int opcao;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Adicionar aviao\n");
        printf("2. Remover aviao\n");
        printf("3. Autorizar decolagem\n");
        printf("4. Autorizar aterrissagem\n");
        printf("5. Exibir avioes cadastrados\n");
        printf("6. Exibir relatorio de voos\n");
        printf("7. Colocar na lista de decolagem\n");
        printf("8. Colocar na lista de aterissagem\n");
        printf("9. Proximas decolagens\n");
        printf("10. Proximas aterrissagens\n");
        printf("11. Quantidade de voos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                insereLDISP(&inicio);
                break;
            case 2:
                removeLDISP(&inicio);
                break;
            case 3:
                removeFDEC(&inicio);
                break;
            case 4:
                removeFATE(&inicio);
                break;
            case 5:
                escreveLDISP(&inicio);
                break;
            case 6:
                escreveRELAT(&inicio);
                break;
            case 7:
                insereFDEC(&inicio);
                break;
            case 8:
                insereFATE(&inicio);
                break;
            case 9:
                proximas_decolagens(&inicio);
                break;
            case 10:
                proximas_aterrissagens(&inicio);
                break;
            case 11:
                quantidade_voos(&inicio);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

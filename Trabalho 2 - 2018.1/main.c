// Desenvolvido por Bárbara Gabriele Lima Luz Santos, Micael de Oliveira Mota e Rafael Correa Nagy

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*
 * Função insere:
 * Insere um novo nó ou atualiza o campo "saldo" de um nó existente.
 *
 */
void insere (arv* A);

/*
 * Função consulta:
 * Verifica a existência de um nó.
 *
 */
void consulta (arv* A);

/*
 * Função ranca:
 * Remove um nó da árvore.
 *
 */
void ranca (arv* A);

/*
 * Função imprime_ordem:
 * Lista as chaves dos nós em ordem crescente [se segundo parâmetro for 'c'] ou decrescente [se segundo parâmetro for 'd'].
 *
 */
void imprime_ordem (arv* A);

/*
 * Função imprime_nivel:
 * Lista as chaves dos nós da árvore que tiverem nível igual ao número fornecido.
 *
 */
void imprime_nivel (arv* A);

/*
 * Função imprime_altura:
 * Informa a altura da árvore.
 *
 */
void imprime_altura (arv* A);

/*
 * Função crescente:
 * Lista as chaves dos nós da árvore em ordem crescente.
 *
 */
void crescente (no* raiz);

/*
 * Função decrescente:
 * Lista as chaves dos nós da árvore em ordem decrescente.
 *
 */
void decrescente (no* raiz);

/*
 * Função percorre_nivel:
 * Percorre o nível indicado.
 *
 */
void percorre_nivel (no* raiz, int target, int qnt);

/*
 * Função relatorio_final:
 * Imprime relatório final com: quantidade de distintos nós na árvore e, para cada nó, os campos "codigo_cliente", "qnt_op" e "saldo".
 *
 */
void relatorio_final (arv* A);

int main () {
    char op;
    arv* A = inicializa_arvore();

    while (scanf("%c", &op), op != 'f') {
        switch (op) {
            case 'i':
                insere(A);
            break;

            case 'c':
                consulta(A);
            break;

            case 'r':
                ranca(A);
            break;

            case 'p':
                imprime_ordem(A);
            break;

            case 'n':
                imprime_nivel(A);
            break;

            case 'h':
                imprime_altura(A);
            break;
        }
    }
    relatorio_final(A);
    free(A);
}

void insere(arv* A) {
    int codigo_cliente, op, val;
    scanf(" %d %d %d", &codigo_cliente, &op, &val);
    insere_no(A, codigo_cliente, op, val);
}

void consulta(arv* A) {
    int codigo_cliente;
    scanf("%d", &codigo_cliente);
    if (!consulta_no(A, codigo_cliente)) {
        printf("nao ");
    }
    printf("existe no com chave: %d\n", codigo_cliente);
}

void imprime_ordem(arv* A) {
    char c;
    scanf (" %c", &c);
    if (c == 'c') {
        crescente(A->raiz);
    }
    else if (c == 'd') {
        decrescente(A->raiz);
    }
}

void imprime_nivel(arv* A) {
    int target;
    scanf("%d", &target);
    if (altura(A->raiz) >= target) {
        percorre_nivel(A->raiz, target, 1);
    }
}

void ranca(arv* A) {
    int codigo_cliente;
    scanf("%d", &codigo_cliente);
    if (consulta_no(A, codigo_cliente)) {
        no* removido = ranca_no(A, A->raiz, codigo_cliente);
        free(removido);
    }
}

void imprime_altura(arv* A) {
    printf("%d\n", altura(A->raiz));
}

void crescente(no* raiz) {
    if (raiz == NULL) return;
    else {
        crescente(raiz->esq);
        printf("%d %d %d\n", raiz->codigo_cliente, raiz->qt_op, raiz->saldo);
        crescente(raiz->dir);
    }
}

void decrescente(no* raiz) {
    if (raiz == NULL) return;
    else {
        decrescente(raiz->dir);
        printf("%d %d %d\n", raiz->codigo_cliente, raiz->qt_op, raiz->saldo);
        decrescente(raiz->esq);
    }
}

void percorre_nivel(no* raiz, int target, int qnt) {
    if (raiz == NULL) return;
    else if (target == qnt) {
        printf("%d\n", raiz->codigo_cliente);
    }
    else {
        percorre_nivel(raiz->esq, target, qnt+1);
        percorre_nivel(raiz->dir, target, qnt+1);
    }
}

void relatorio_final (arv* A) {
    printf("-+- Inicio relatorio -+-\n%d\n", A->tam);
    while (A->raiz != NULL) {
        no* removido = ranca_no(A, A->raiz, A->raiz->codigo_cliente);
        printf("%d %d %d\n", removido->codigo_cliente, removido->qt_op, removido->saldo);
        free(removido);
    }
    printf("-+- Fim relatorio -+-\n");
}

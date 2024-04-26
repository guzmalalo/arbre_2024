#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition d'un noeud
typedef struct N {
    // clé
    int n;

    // Information à stocker
    char nom[50];

    // Lien d'hierarchie
    struct N *gauche; // Noued à gauche
    struct N *droite; // Noued à droite

} Node;

void creerNoeud(Node **arbre_n, int n, char *str) {

    // Allocation de memoire (Creation du noued)
    // et recuperation de son adresse
    (*arbre_n) = (Node *) malloc(sizeof(Node));

    // Initialisation du noued
    (*arbre_n)->n = n;
    strcpy((*arbre_n)->nom, str);

    // Initialisation des noueds fils
    (*arbre_n)->droite = NULL;
    (*arbre_n)->gauche = NULL;
}

void ajouterNoeud(Node **p_arbre, int n, char *str) {
    // Creation d'un pointeur temporaire vers
    // le sous-arbre
    Node *arbre = *p_arbre;

    if (arbre == NULL) {
        creerNoeud(p_arbre, n, str);
    } else if (n < arbre->n) {
        ajouterNoeud(&(arbre->gauche), n, str);
    } else if (n > arbre->n) {
        ajouterNoeud(&(arbre->droite), n, str);
    } else {
        printf("Clé existante, impossible d'ajouter: %s \n", str);
    }
}


void libererArbre(Node **arbre) {
    if (*arbre == NULL) {
        return;
    }
    libererArbre(&(*arbre)->gauche);
    libererArbre(&(*arbre)->droite);
    free(*arbre);
}


void afficheInfixe(Node *arbre) {

    if (arbre == NULL)
        return;
    afficheInfixe(arbre->gauche);
    printf("%d:%s\t", arbre->n, arbre->nom);
    afficheInfixe(arbre->droite);
}

void affichePrefixe(Node *arbre) {
    if (arbre != NULL) {
        printf("%d:%s\t", arbre->n, arbre->nom);
        affichePrefixe(arbre->gauche);
        affichePrefixe(arbre->droite);
    }
}

void affichePostfixe(Node *arbre) {
    if (arbre != NULL) {
        affichePostfixe(arbre->gauche);
        affichePostfixe(arbre->droite);
        printf("%d:%s\t", arbre->n, arbre->nom);
    }
}


int main() {
    // Initialisation de l'arbre
    Node *arbre = NULL;

    // Creation du premier noued (racine)
    ajouterNoeud(&arbre, 10, "Burger");

    // Ajout des noueds à trier
    ajouterNoeud(&arbre, 42, "Frites");
    ajouterNoeud(&arbre, 1, "Kebab");
    ajouterNoeud(&arbre, 80, "Pizza");
    ajouterNoeud(&arbre, 80, "Tacos"); // pas de doublons

    // Affichage
    printf(" \n Affichage Infixe \n");
    afficheInfixe(arbre);
    printf(" \n Affichage Prefixe \n");
    affichePrefixe(arbre);
    printf(" \n Affichage Postfixe \n");
    affichePostfixe(arbre);

    libererArbre(&arbre);

    return 0;
}

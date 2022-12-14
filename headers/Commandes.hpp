/*
    SHUTDWON : appeller le programme
    arguments :
    
        -> -af   : definir un commutateur d'arrêt forcé
        
        -> -rd   : definir un commutateur de redemarage 
        
        -> -an   : definir un commutateur d'arrêt normal
        
        -> -t<n> : definir la durée d'attente avant l'arrêt du système
            <-> n la durée de temps , en secondes(s) en minutes(mn) et en heures(h)

        -> -stop : arrête le compteur et annule l'arrêt du système
         



*/

/**
 * @file 
*/

// modification pour git 

//git diff 

#ifndef COMMANDES_HPP
#define COMMANDES_HPP

#include <string>
#include <vector>
#include <cstring>
#include <array>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <functional>

#include "SHUT.hpp"


//commit test 
//line

//MACROS
#define TAILLE_TABLE_COMANDES 5
#define msgINVALID "INCORRECT"
#define SEPARATEUR_ARG_OUVRANT '['
#define SEPARATEUR_ARG_FERMANT ']'

//macros debug
////////////////////////////////////////
#define DEBUG_PROG 1 

//conditions macro debug
#if DEBUG_PROG == 0

#define Dmsg(str)(std::cout<<str)
#define DmsgEndl(str)(std::cout<<str<<std::endl)


#else

#define Dmsg(str)(str)
#define DmsgEndl(str)(str)

#endif
////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
//alias

/// @brief alias de la specialisation std::vector<std::string> pour stocker les commandes 
using stdStab = std::vector<std::string> ;
using comTab = std::array<std::pair<std::string , int> , TAILLE_TABLE_COMANDES> ;
using comInfo = std::pair<std::string , int>;
using stdComPile = std::stack<int>;

////////////////////////////////////////////////////////////////////////////////////////////////////////:



/////////////////////////////////
// déclarations externes 

/**
 * @brief stocke l'identifaint de toute les instructions
 * @details espace de stockage consulté lors de la construction de la pile des commandes ,
 * il contient les noms des drapeaux de commandes et leurs identifiants , le constructeur de pile de commande
 * se refère à cette table pour empiler les commandes  
 * 
*/
extern comTab TABLE_DES_COMMANDES;


///////////////////////////////////




/**
 * @brief converti un tableau de chaines c en un stdStab
 * @details
 * @param[in] argv tableau de chaînes style c
 * @param[in] taille taille du tableau de chaînes c
 * @returns le vecteur de chaines sous forme de stdStab
*/
stdStab convertir_chaine(char* argv[] , int taille);

void afficherStab(const stdStab & tab);

//fonctions pour l'interpretation des commandes 

/**
 * @brief construit une pile de commande à partir de l'entree utilisateur 
 * @details analyse chaque commande entrée par l'utilisateur et verifie si elle existe dans 
 * la table des commandes . Ensuite elle traduit cette liste par une pile de commandes
 * @param[in] stdStab tableau de chaines , vecteur de commandes 
 * @pre la commande doit être valide 
 * @post la pile de commande sera construite et pourra être utilisée par l'executeur 
 * @exception Envoi une exception de type std::invalid_argument si l'argument entree par l'utilisateur n'a pas de sens 
*/
stdComPile interpreter_Stab(const stdStab& ListeArguments);

/**
 * @brief verifie si la commande contient des arguments ou si elle est juste un drapeau simple
 * @param commande liste d'arguments 
 * @return envoi un std::pair<std::string ,bool> qui contient la chîne de caractère du drapeau et un bool 
 * qui est à 1 si la commande a des arguments , 0 dans le cas contraire 
 *
*/
std::pair<std::string , bool> est_commande_argument(const std::string & commande); //DEBUG F1

/**
 * @brief récupère les arguments numériques entrés par l'utilisateur lors de l'appel du programme 
 * @details au lieu de s'interesser aux drapeaux comme interpreter_Stab() cette fonction s'atarde sur les caractères générés  
 * par l'utilisateur et qui se retrouvent dans le champ des arguements tel que : "()" , "[]" , "<>" .
 * par exemple : -drapeau[argument] , la fonction retournera "argument" 
 * @param
*/
std::stack<std::string> recup_arg(const stdStab& ListeArguments); //DEBUG F2

/**
 * @brief converti une ligne de commande en tableau d'arguments de type stdStab
*/
stdStab conversion_chaine_caractere(const std::string& chaine);




// executeur de commandes 

/**
 * @brief analyse la pile de commande et execute une commande en fonction de l'id 
 * @details l'orsqu'on lui passe une pile de commande , l'executeur parcour cette dernière executant une commande en 
 * en fonction de son identifiant
 * @param duree la duréé à modifier pour la commande -t 
 * @param commutateur le commutateur à modifier pour les commandes : -an , -af , -rd , -stop 
 * @param pile_commande la pile à analyser qui contient la liste des commandes à éxecuter 
 * @param liste_param la liste des arguments pour les commandes 
 * @pre la pile passée doit au moins contenir un élement et l'id de la commande de temps doit y figurer obligatoirement 
 * @post à la fin de la fonction , la pile sera vide et devra être rechargé avec une nouvelle entrée utilisateur 
 * 
*/
void executeur(std::chrono::duration<double> & duree , Acom&  commutateur , stdComPile & pile_commande , 
               std::stack<std::string> & liste_param );

#endif
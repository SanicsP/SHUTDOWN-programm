#ifndef SHUT_HPP
#define SHUT_HPP

#include <functional>
#include <thread>
#include <future>
#include <limits>
#include <atomic>
#include <cstdlib>


/**
 * @file
*/


/** 
 *  @brief Represente les commutateurs de l'arrêt du système 
 *  @details AF signifie arrêt forcé , AN signifie arrêt normal , RD signifie redemarage
 *  @enum 
*/
enum class Acom : int
{
    AF   = 0, /// @brief arrêt forcé
    AN   = 1, /// @brief arrêt immédiat 
    RD   = 2, /// @brief redemarage 
    ANUL = 3, /// @brief annuler 

};


/// @brief stocke la fonction qui sera appelée à la fin du programme 
extern std::function<void()> fonction_de_fin; 

/**
 * @brief definie la fonction qui sera invoquée à la fin du programme 
 * @pre la fonction invoquée ne doit retourner auccune valeur et ne doit prendre aucun arguement 
 * @param[in] std::function<void()> la fonction à invoquer   
*/
void definir_class_fin(std::function<void()> ff);
/**
 * @brief thread gérant la partie communication entre le programme et l'utilisateur 
 * @details thread exécutant la partie du logiciel dediée à la communication entre l'utilisateur et le programme
 * communique en écriture et en lecture avec le thread du compteur , ce pont est nécessaire afin de définir le temps
 * d'attente avant l'arret du système et aussi d'être au courant de ce dernier. même si le thread éxecute une fonction 
 * de type void() elle retourne via un std::promise<Acom> le commutateur défini par l'utilisateur celui ci servira à l'arrêt 
 * du système.
 * 
 * @param t_duree duree qui sera d'abord définie par l'utilisateur et envoyée au thread du compteur 
 * @param Pmsg_duree_compteur message qui sera envoyé au thread du compteur après que la durée soit définie 
 * ce message contient la valeur de durée pour initialiser le compteur 
 * @param Fmsg_arret_partie_com message envoyé par le thread du compteur notifiant l'ordre d'arrêt de ce 
 * thread(thread_compteur)
 * @param Pmsg_arret_compteur message qui sera envoyé au thread du compteur l'ordonnant d'arrêter l'execution 
 * de ce dernier 
 * @param argv tableau de chaînes style c récupéré lors de l'ouverture du programme via la ligne de commandes 
 * @param argc taille du tableau de chaînes de style c
 * @param Pmsg_commutateur retour de la valeur du commutateur qui servira à déterminer le type d'arret système 
 * @returns ne retourne rien en tant que fonction mais en réalité le thread enverra un message notifiant la valeur du 
 * commutateur . donc le type de retour est Acomm
*/
void thread_commande(const std::chrono::duration<double> & t_duree , 
                    std::promise<std::chrono::duration<double>> && Pmsg_duree_compteur ,
                    std::future<bool>&& Fmsg_arret_partie_com ,
                    std::promise<bool>&& Pmsg_arret_compteur ,
                    char* argv[] , int argc , std::atomic<Acom> & ATCmsg_commutateur , std::mutex & verroux_flux_sortie
                    );

void thread_compteur(std::promise<bool>&& Pmsg_arret_partie_com ,
                     std::future<std::chrono::duration<double>>&& Fmsg_duree_compteur ,
                     std::future<bool>&& Fmsg_arret_compteur , std::mutex & verroux_flux_sortie
                    );

//fonction de fin du programme 

void messages ();
void fonction_fin_programme(Acom commutateur);

void arret_systeme(Acom commutateur);
#endif
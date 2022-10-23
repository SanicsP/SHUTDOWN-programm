#ifndef SHUT_HPP
#define SHUT_HPP
#include <functional>
#include <thread>
#include <future>


/**
 * @file
*/


/** 
 *  @brief Represente les commutateurs de l'arrêt du système 
 *  @details AF signifie arrêt forcé , AN signifie arrêt normal , RD signifie redemarage
 *  @enum 
*/
enum class Acom
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


void thread_commande(std::chrono::duration<double> & t_duree);

void thread_compteur(std::chrono::duration<double> & t_duree);







#endif
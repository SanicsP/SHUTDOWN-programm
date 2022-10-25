#ifndef TEST_LIB_HPP
#define TEST_LIB_HPP

#include <iostream>
#include<chrono>



/**
* @file
*/

/*
 * @struct Compteur
 * @brief classe de base qui fait office de compteur
 * @details classe utilisée affin de pouvoir compter le temps depuis un point dans le temps pécis
 * elle peut par de ce fait gérer le temps du programme 
*/
class compteur
{

public:

    compteur() = delete;
    
    /**
      *@brief constructeur par défaut de la classe compteur  
      *@param[in] double la duree à laquelle devra compter le compteur 
      *@returns ne retourne rien
    */
    compteur(double duree) noexcept;

    /**
      *@brief verifie si le compteur à atteint la durée cible 
      *@returns true , si le compteur a atteint la duree cible , false dans le cas contraire.
    */
    bool estFini() noexcept;
    
    /**
      *@brief recommence le compteur depuis zéro
      *@returns ne retourne rien
    */
    void renitialiser() noexcept;

    /**
     * @brief relance le compteur depuis zéro et redefini un nouveau temps cible 
     * @param[in] double Nouveau temps cible
    */
    void redef(double duree) noexcept;
    /**
     * @brief renvoi la durée actuel du compteur 
     * @returns ne retourne rien
    */
    double actuel() const noexcept;

private:
    
    ///@brief Instant du début du compteur 
    std::chrono::duration<double> m_temps_cible;
    
    ///@brief Temps cible
    std::chrono::time_point<std::chrono::steady_clock>  m_temps_initial; 

    ///@brief Etat du compteur
    bool m_temps_ecoulee;

};

/**
 * @brief verifie si l'argument est une durée 
 * @details verifie les données entrées par l'utilisateur dans le champ des arguments 
 *  
 * @param parametre chaine de caractères de paramètres
 * @return 1 si l'aguement est une durée , 0 dans le cas contraire 
 * @code
 *  std::string duree{"2h"};
 *  est_duree(duree); // vaut true
 *  
 *  duree = "300s";
 *  est_duree(duree); // vaut true
 * 
 *  duree = "60mn" 
 *  est_duree(duree) // vaut true
 * 
 *  duree = "60jours"; // unité non reconnue 
 *  est_duree(duree) // vaut false
 
 * @endcode
*/
bool est_duree(const std::string& parametre);

/**
 *
 * @brief convertie une chaine de caractère de type std::string en std::chrono::duration<double>
 * @details convertie des valeurs de durée litérales entrées par l'utilisateur , en valeurs de 
 * std::chrono::duration<double> 
 * @param parametre chaine de caractère de la valeur litérale 
 * @return une durée sous forme de std::chrono::duration 
 * @pre la valeur litérale doit être soit en : unité de secondes , d'heures ou de minutes 
 * @post la valeur retournée sera un std::chrono::duration<double> avec déclaration implicite <double , std::ratio<1>> cela 
 * signifie qu'un tick représente une seconde , la conversion vers les secondes se fera toute seule , la duree sera entière 
*/
std::chrono::duration<double> conversion_duree(const std::string& parametre);




#endif

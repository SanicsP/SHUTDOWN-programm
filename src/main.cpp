#include "Compteur.hpp"
#include "SHUT.hpp"
#include "Commandes.hpp"
#include "TESTS.hpp"


#include <iostream>




int main(int argc , char* argv[])
{
   
    //test unbitaires 
        tu_Commandes();
        tu_Compteur();
        tu_SHUT();
    ///
   
    
    stdStab tab = convertir_chaine(argv , argc);
    interpreter_Stab(tab);

    std::vector<std::string> liste_param{};
    liste_param = recup_arg(tab);

    std::cout<<"recuperation des argumments "<<std::endl;
    if(!liste_param.empty()){
        std::cout<<"parametre 1 : "<< liste_param[0]<<std::endl;;
        std::chrono::duration<double> duree = conversion_duree(liste_param[0]);
        std::cout<<"duree en secondes : "<<duree.count()<<" s  soit "<<duree.count()/3600<<" heures et , "<< duree.count()/60<<" minutes"<<std::endl;
    }
    
    std::string comm;
    std::getline(std::cin , comm);
    stdStab tab2 = conversion_chaine_caractere(comm);
    //std::cout<<'\n'<<std::endl;
    afficherStab(tab2);

    std::cout<<"taille du tableau : "<<tab2.size()<<std::endl;
    
    std::cin.ignore();
    return 0;
}
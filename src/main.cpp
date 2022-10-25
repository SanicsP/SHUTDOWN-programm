#include "TESTS.hpp"


#include <iostream>




int main(int argc , char* argv[])
{
   
    //test unbitaires 
        tu_Commandes();
        tu_Compteur();
        tu_SHUT();
    ///
   Acom com;
    std::chrono::duration<double> duree{};
    stdComPile pile_com;
    stdStab tab = convertir_chaine(argv , argc);
    pile_com = interpreter_Stab(tab);

    std::stack<std::string> liste_param{};
    liste_param = recup_arg(tab);

    std::cout<<"recuperation des argumments "<<std::endl;

    if(!liste_param.empty()){
       executeur(duree , com , pile_com ,liste_param );
       std::cout<<" la duree est de "<<duree.count()/3600 <<"minutes \n";
       std::cout<<" le numero du commutaeur est "<< static_cast<int>(com) <<"\n";


       
       
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
#include "TESTS.hpp"


#include <iostream>




int main(int argc , char* argv[])
{
   
    //test unbitaires 
        tu_Commandes();
        tu_Compteur();
        tu_SHUT();
    ///

    std::chrono::duration<double>  t_duree ;
    
    std::promise<std::chrono::duration<double>>  Pmsg_duree_compteur ;
    std::promise<bool> Pmsg_arret_compteur ;
    std::promise<Acom>  Pmsg_commutateur;
    std::promise<bool> Pmsg_arret_partie_com ;

    std::future<bool> Fmsg_arret_partie_com = Pmsg_arret_partie_com.get_future(); 
    std::future<std::chrono::duration<double>>Fmsg_duree_compteur = Pmsg_duree_compteur.get_future();
    std::future<bool>Fmsg_arret_compteur = Pmsg_arret_compteur.get_future();

    std::thread thread_partie_commande(thread_commande, t_duree , std::move(Pmsg_duree_compteur) 
                                     , std::move(Fmsg_arret_partie_com)  , std::move(Pmsg_arret_compteur), 
                                       argv , argc , std::move(Pmsg_commutateur));
    std::thread thread_partie_compteur(thread_compteur , std::move(Pmsg_arret_partie_com ), std::move(Fmsg_duree_compteur) 
                                      , std::move(Fmsg_arret_compteur)
      );

    thread_partie_commande.join();
    thread_partie_compteur.join();


    std::cin.ignore();
    return 0;
}
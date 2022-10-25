#include "TESTS.hpp"

void tu_Commandes()
{

    
//test fonction convertir_cahine ***************************************************************
    char* argv[] = {
        "NOM_DU_PROGRAMME_NE_PAS_RECUPER"
        "bonjour",
        "je",
        "suis",
        "une",
        "commande"
    };
    int argc = 6;
    
    stdStab tab_test1 = convertir_chaine(argv , argc);
    
    stdStab tab_comparatif { 
        "bonjour",
        "je",
        "suis",
        "une",
        "commande"
    };
    assert(tab_test1 == tab_comparatif && "presence de bug dans la fonction convertir_chain() : comportement innatendu");

////////////////////////////////////////////////////////////////////////////////////////////////////:


//test de fonction interpreter Stab ********************************************************************
    stdComPile pile_teste = interpreter_Stab( 
        {
            "-t[45]" , "-an" , "-af" , "-rd" , "-stop"
        
        }
    );

    stdComPile pile_comparatif;
    pile_comparatif.push(0);
    pile_comparatif.push(3);
    pile_comparatif.push(1);
    pile_comparatif.push(2);
    pile_comparatif.push(4);
    assert(pile_teste == pile_comparatif && "presence de bugg dans la fonction interpreter Stab , comportement indeterminé");

    std::string arg[5] = {
        "-t[45]" , "[hahahfahzf][45]" , " n'i[1]m[2]porte_quoi" , "arg[1]]" , "arg]32["
    };
    assert(est_commande_argument(arg[0]).second && !est_commande_argument(arg[1]).second && !est_commande_argument(arg[2]).second 
            && !est_commande_argument(arg[3]).second && !est_commande_argument(arg[4]).second && 
            "presence de bugs dans la fonction est_commande_argument comportement indeterminé "
    );
    assert(est_commande_argument(arg[0]).first == "-t" && 
    "presence de bugs dans la fonction est_commande_argument comportement indeterminé ");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//test de la fonction recup_arg ****************************************************************************
    std::stack<std::string> list_arg_test = recup_arg( 
        {"-t[45h]"}
        
    );
    assert(list_arg_test.top() == "45h" && "presence de bugs dans la fonction recup_arg() comportement indeterminé");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//test de la fonction conversion_chaine_caractere**************************************************
    const std::string mauvaise_entree_u = "    arg1 arg2 arg3[]  ....     34   56    12   -m -an ";
    stdStab comparatif = {
        "arg1" , "arg2" , "arg3[]" , "...." , "34" , "56" , "12" , "-m" "-an"
    };

    assert(conversion_chaine_caractere(mauvaise_entree_u) == comparatif && 
    "presence de bugs dans la fonction conversion_chaine_caractere() comportement indeterminé");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//tests de l'executeur*************************************************************************************
    stdStab tab_test = {
        "-t[45h]" "-an"
    };
    std::chrono::duration<double> duree_t {0};
    Acom commutateur_test;
    stdComPile pile_com_test = interpreter_Stab(tab_test);
    std::stack<std::string> liste_param_test = recup_arg(tab_test);

    executeur(duree_t , commutateur_test , pile_com_test , liste_param_test);

    assert(duree_t.count() / 3600 == 45 && commutateur_test == Acom::AN && "presence de bugs dans l'executeur , comportement indetermine");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    


}

void tu_SHUT()
{

}

void tu_Compteur()
{


}

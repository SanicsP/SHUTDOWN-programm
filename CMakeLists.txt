set(project_name SHUTDOWN)

#chemin relatif
set(r_src_dir src)
set(r_hd_dir header)

# bibliothèques 


project(${project_name})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)


set(main_source 
    ${r_src_dir}/main.cpp
)


#variable pour les fichiers sources servant à la bibliothèque de comptage 
set(libCompteur_sources
    ${r_src_dir}/Compteur.cpp
)
# #variable pour les fichiers sources servant à la bibliothèque d'arrêt du programme
set(libSHUT_sources 
    ${r_src_dir}/SHUT.cpp
)
# #variable pour les fichiers sources servant à la bibliothèque des interprets de commande 
set(libCommandes_sources 
    ${r_src_dir}/Commandes.cpp
)
#variables pour les fichiers sources servant à la bibliothèque des tests unitaires et exceptions 
set(libTESTS_sources
    ${r_src_dir}/TESTS.cpp
)

#inclusion des chemin 
include_directories(headers) 



#ajour de bibliothèque d'arrêt du programme
add_library(libSHUT ${libSHUT_sources})


#ajour de bibliothèque des tests
add_library(libTESTS ${libTESTS_sources})

#ajour de bibliothèque d'interpret des commandes et du compteur 
add_library(libCommandes ${libCommandes_sources} ${libCompteur_sources})




#construction du programme 
add_executable(${project_name} ${main_source})
target_link_libraries(${project_name} libSHUT libTESTS libCommandes)

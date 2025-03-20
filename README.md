# DDR_FPGA
Le but de ce projet est de développer un jeu vidéo sur un FPGA à l'aide de Litex.\
Nous avons choisi Dance Dance Revolution comme jeu vidéo.\
C'est un jeu vidéo de rythme qui vise à reproduire une chorégraphie en appuyant sur un tapis de danse composé de flèches avec ses pieds.\
Vous pouvez voir un exemple ici : [Vidéo Dance Dance Revolution](https://www.youtube.com/watch?v=T2e1tsnKkiI)\
La carte FPGA à notre disposition est une NexysA7-50T de Digilent.\
LiteX est un framework facile d'utilisation et efficace qui fourni une infrastructure pour créer des Cores/SoCs FPGA.\
Vous pouvez retrouver ce framework à l'adresse suivante : [Github Litex](https://github.com/enjoy-digital/litex) 

## Contenu
Ce dossier contient tous les fichiers/dossiers nécessaires à l'implémentation du processeur sur le FPGA.

| Nom                     | Description                                                                  |
|-------------------------|------------------------------------------------------------------------------|
| [README.md](README.md)  | Les étapes d'installation                                                    |
| [setup.sh](setup.sh)    | Télécharger et installer les modules nécessaires                             |
| [digilent_nexys4ddr_platform.py](digilent_nexys4ddr_platform.py) | Décrire sa plateforme               |
| [digilent_nexys4ddr_target.py](digilent_nexys4ddr_target.py) | Décrire sa cible                        |
| [build_nexys4ddr.sh](build_nexys4ddr.sh) | Construire la cible                                         |
| [load_nexys4ddr.sh](load_nexys4ddr.sh)      | Charger le bitstream                                     |
| [compile_firmware.sh](compile_firmware.sh)        | Compiler le firmware                               |
| [load_firmware.sh](load_firmware.sh)  | Lancer le load et implémenter le firmware compilé              |
| [firmware](firmware)    | Dossier incluant les fichiers en langage C nécessaires au firmware           |
| [module](module)    | Dossier incluant les modules écrits en Python nécessaires pour décrire la cible  |


## Installation

### Prérequis
- Python 3.5+
- Outils de développement Vivado de Xilinx : [https://www.xilinx.com/support/download.html](https://www.xilinx.com/support/download.html)
- Outils en ligne de commande Digilentinc : [https://reference.digilentinc.com/reference/software/adept/start](https://reference.digilentinc.com/reference/software/adept/start)
  - Récupérer les Utilities - [Latest Downloads](#)

## Préparation et lancement de la démo
```bash
# Installation de LiteX et de ses dépendances
./setup.sh

# Construction du SoC
./build_nexys4ddr.sh

# Chargement du bitstream sur le FPGA
./load_nexys4ddr.sh

# Compilation du firmware
./compile_firmware.sh

# Chargement du firmware dans le SoC
./load_firmware.sh
```
Après avoir fait ceci on se retrouve sur le terminal du SoC.\
Il faut appuyer une fois sur Entrée. Vous devriez voir ceci :

```bash
litex\
```

Il faut alors taper la commande reboot puis appuyer sur Entrée :

```bash
litex\reboot
```
Vous devez maintenant voir s'afficher ceci :

```bash
    ___                          ___                         __                 _       _   _             
   /   \__ _ _ __   ___ ___     /   \__ _ _ __   ___ ___    /__\ _____   _____ | |_   _| |_(_) ___  _ __  
  / /\ / _` | '_ \ / __/ _ \   / /\ / _` | '_ \ / __/ _ \  / \/// _ \ \ / / _ \| | | | | __| |/ _ \| '_ \ 
 / /_// (_| | | | | (_|  __/  / /_// (_| | | | | (_|  __/ / _  \  __/\ V / (_) | | |_| | |_| | (_) | | | |
/___,' \__,_|_| |_|\___\___| /___,' \__,_|_| |_|\___\___| \/ \_/\___| \_/ \___/|_|\__,_|\__|_|\___/|_| |_|

                            Developed by Antoine Madrelle and Tangi Brandeho
                                                                                                          
Dance Dance Revolution App built on 20/03/25 16.11

Available commands:
help               - Show this command
reboot             - Reboot CPU
led                - Led demo
ddr                - Dance Dance Revolution

dance-dance-revolution-app\
```

## Architecture SoC
Le choix du processeur s'est porté sur un picorv32 car il ne prend pas beaucoup de mémoire. Ce processeur est cadencé à 100MHz.\
Autour nous avons attribué de la ROM (32 KiB), de la SRAM (128 KiB) et de la DRAM (128MiB).\
Ensuite nous avons déclaré les différents modules dont nous avions besoin autour de ce processeur pour constituer notre SoC.\
A noter que certains modules font déjà parti de Litex et donc il faut les appeler via une fonction pour les inclure dans le SoC.\
Tandis que pour les autres il faut les définir.

### VGA
Le VGA choisi est un format SVGA (Super Video Graphics Array) en 60 Hz. Donc cela correspond aux dimensions 800x600 pixels selon les standards que l'on peut retrouver ici : [Spécification SVGA 800x600](http://www.tinyvga.com/vga-timing/800x600@60Hz)\
On se retrouve donc avec une pixel clock de 40 MHz.\

### Framebuffer
Le framebuffer est comme son nom l'indique un buffer qui va stocker l'image à envoyer au controleur VGA via DMA.\
Le format de chaque pixel stocké est en RGB332, donc un octet pour chaque pixel. Ce qui nous fait 800 * 600 * 8 = 480 KB\
Le choix du format RGB332 a été fait pour réduire au maximum la taille du framebuffer à transmettre via DMA.\
Lorsque l'on instancie des modules on ajoute également des registres pour venir les piloter.

### 7 segments
Nous avons instancié 8 blocs de 7 segments.

### Boutons
Les 5 Boutons de la carte ont été instanciés.

### Leds
Les 16 Leds de la carte ont été instanciées.

**IMAGE**

## Architecture Jeu

### main
Dans le main.c nous retrouvons la console qui va nous permettre de reboot, d'afficher une demo de led, d'afficher une aide ou bien de lancer le jeu Dance Dance Revolution.

### delay
Nous retrouvons des fonctions qui permettent de lancer des timers avec le temps souhaité en microseconde ou milliseconde.

### display
Ici se trouve les fonctions et les define qui vont permettre d'utiliser les affichages 7 segments.

### drawings
Là se trouve toutes le fonctions qui vont nous permettre de dessiner dans le framebuffer.\
On peut dessiner des carrés, des flèches et également effacer l'écran. On peut spécifier la couleur que l'on veut pour chacun de ces éléments.\
Pour les flèches il est possible de choisir la direction souhaitée.

### music
Ici on trouve la structure qui contient les temps auxquels doivent apparaîtrent chaque flèche et dans quelle direction.\
Dans une partie suivante nous pourrons voir le code que nous avons crée qui permet à partir d'une musique quelconque d'en sortir des temps et directions de flèches en fonction de son rythme.

### ddr
ddr est est le diminutif de Dance Dance Revolution. C'est donc ici que la mécanique principale du jeu se déroule.\
Cette partie contient également des fonctions qui vont permettre de mettre en œuvre une interruption sur le timer.\
De base sur Litex, seul l'interruption de l'Uart est activée. Il faut donc l'activer dans un premier temps.\
Ensuite il faut régler le timer. Nous avons fait le choix que le timer compte les centièmes de secondes car les temps des flèches sont précises au centième de seconde.\
Donc à chaque fois que le timer arrivera à 0, l'interruption s'activera la fonction correspondante s'éxecutera. Cette fonction va venir incrémenter un compteur.\
Ensuite dans une boucle on va regarder ce compteur pour savoir quand afficher une flèche.\
Qaund une flèche doit être affichée on ajoute dans un tableau une structure qui contient sa position et sa direction.\
Toutes les 10 millisecondes on va rafraîchir les positions des flèches afin qu'elles montent.\
Le but du jeu est d'appuyer sur les boutons correspondants aux directions lorsque les flèches arrivent dans les carrés.\
Donc dans la boucle de jeu on regarde l'appui des boutons. Sur un appui d'un bouton on va vérifier si une flèche se trouve dans un carré.\
Plus la flèche est proche du centre du carré alors plus on marque de points. A savoir que si la flèche n'est pas dans le carré alors on perd des points.\
On ne peut pas aller en dessous de 0 points. Le score est mis à jour sur les affichages 7 segments à chaque boucle.\
Les flèches sont effacées du tableau lorsqu'elles sortent de l'écran.\
Le jeu s'arrête lorsque le joueur appuie sur les 5 boutons en même temps.

## Déroulement du jeu
Lorsque l'on lance le jeu en tapant la commande ddr la démonstration avec des flèches se lance.\
Des flèches montent alors vers les carrés blans en haut.\
Il faut appuyer sur les boutons correspondants aux bonnes directions des flèches lorsque celles-ci arrivent dans les carrés blancs.\
Le score s'affiche alors en temp réel sur les affichages 7 segments.\
Une fois qu'il n'y a plus de flèches et que vous avez pu voir votre score vous pouvez appuyer sur tous les boutons en même temps afin de sortir de la boucle de jeu et retourner à la console.

**VIDEO**

## Problèmes à résoudre
Problème avec l'affichage. On peut voir un clignotement lors du rafraichissement de l'image.\
La piste est de déclarer soit même son module et de ne pas utiliser celui de litex. Mais pourtant en ayant vérifié le code source du VGA de litex il semble bien codé.\
Pas de musique pour l'instant.\
Pas de gamepad. USB HID

## Mettre ce qui permet de télécharger une musique et de la transformer en timestamps

## Auteurs
Dans le cadre d'un projet d'application système à l'ENSTA Bretagne, Tangi Brandého et Antoine Madrelle ont réalisé ce projet.


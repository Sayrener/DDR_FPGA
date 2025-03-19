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
## Architecture SoC

Le choix du processeur s'est porté sur un picorv32 car il ne prend pas beaucoup de mémoire.\
Autour nous avons attribué de la ROM, de la SRAM et de la DRAM.\
Ensuite nous avons déclaré les différents modules dont nous avions besoin autour de ce processeur pour constituer notre SoC.\
VGA (Décrire le VGA)\
100MHz taille sram dram rom \
Framebuffer\
7 segments\
Boutons\
Leds\
(Décrire les différents modules)\
A noter que certains modules font déjà parti de Litex et qu'il suffit d'appeler une fonction pour les inclure dans le SoC.\
Tandis que pour les autres il faut les définir.\
Ajout d'interruption sur le timer

## Architecture Jeu



## Déroulement du jeu

## Problèmes à résoudre
Problème avec l'affichage. On peut voir un clignotement lors du rafraichissement de l'image.\
La piste est de déclarer soit même son module et de ne pas utiliser celui de litex. Mais pourtant en ayant vérifié le code source du VGA de litex il semble bien codé.\
Pas de musique pour l'instant.\

Mettre ce qui permet de télécharger une musique et de la transformer en timestamps



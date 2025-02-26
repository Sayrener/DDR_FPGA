# DDR_FPGA

Dance Dance Revolution sur un picorv32 chargé sur une carte NexysA7-50T

## Contenu

Ce dossier contient tous les fichiers/dossiers nécessaires à l'implémentation du processeur sur le FPGA.

| Nom                     | Description                                                        |
|-------------------------|--------------------------------------------------------------------|
| [README.md](README.md)  | Les étapes d'installation                                          |
| [setup.sh](setup.sh)    | Télécharger et installer les modules nécessaires                   |
| [digilent_nexys4ddr_platform.py](digilent_nexys4ddr_platform.py) | Décrire sa plateforme     |
| [digilent_nexys4ddr_target.py](digilent_nexys4ddr_target.py) | Décrire sa cible              |
| [build_nexys4ddr.sh](build_nexys4ddr.sh) | Construire la cible                               |
| [load_nexys4ddr.sh](load_nexys4ddr.sh)      | Charger le bitstream                           |
| [compile_firmware.sh](compile_firmware.sh)        | Compiler le firmware                     |
| [load_firmware.sh](load_firmware.sh)  | Lancer le load et implémenter le firmware compilé    |
| [firmware](firmware)    | Dossier incluant les fichiers en langage C nécessaires au firmware |


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

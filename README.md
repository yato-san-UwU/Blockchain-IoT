# Blockchain-IoT
Projet de fin d'étude, simulation d'un réseau IoT ou le but est de gérer la confiance entre les différents nœuds IoT grâce à la blockchain.

Implémentation de la solution "Trust Management in Decentralized IoT Access Control System".


Utilisation de :
1) la blockchain ethereum.
2) python avec brownie lien "https://eth-brownie.readthedocs.io/en/stable".   (version de python 3.9)
3) ganache "https://trufflesuite.com/ganache/".
4) solidity pour les smartcontract "https://docs.soliditylang.org/en/latest/".

video explicative pour comprendre un peu comment tout ça marche "https://www.youtube.com/watch?v=M576WGiDBdQ".


les fichiers importants : 
1) reseau.sol dans le dossier contracts (le code solidity)
2) deploy.py scripts
3) le fichier multipletest.py est le pour test plusieur cas 
4) les autres fichier ce cree automatiquement


lancer le programme : 

brownie init //crée un dossier
brownie networks list // voir les reseaux dispo
brownie networks add {network_class} {your_network_name} host={your_host} chainid={your_chaid}  // crée un nouveau reseaux ( attaché ganache avec brownie )
  ""exemple : brownie networks add Ethereum ganache-local host=http://0.0.0.0:8545 chainid=1337""
brownie run scripts/deploy.py --network "nom de reseaux"

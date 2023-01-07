from multiprocessing.sharedctypes import Value
from os import access
from brownie import accounts, reseau, config
from eth_account import Account
from pyrsistent import v
import random

def creation_noued():
    
    print(" assiagnation du noued 0 comme noued SP (amdin) et donc comme mineur")

    # l'admin  lui qui deploi les contract
    account= accounts[0]
    reseau_connect= reseau.deploy({"from":account})

    # ajoue du SP 
    for i in [0]:
        reseau_connect.addSP(accounts[i],'SP')
    
    print("\n")
    print("ajoue du noued Admin")
    print("\n")

    F = random.randint(0,10)
    print("valeur de confiance random pour le noued 5 = ",F)

    # ajoue des SC
    for j in [1, 2, 3, 4, 5]:
        
        # condition pour definir les valeurs de confiance des noueds
        if j == 1:
            val = 9;

        elif j == 2:
            val = 6;

        elif j == 3:
            val = 4;

        elif j == 4:
            val =1;

        else :
            val = F;
        
        reseau_connect.addNoueds(accounts[j],0 + j,'SC'+str(j), val)

    print("\n")
    print("creation des 5 SC ")
    print("\n")

    # transaction 
    # rajouter une transaction de l'admin vers les compte pour leur dire si la transaction est valide ou pas
    
    print("\n")
    print("envoie de 20 ether au contract pour faire la demande d'acces")
    print("\n")

    for j in range(1,6):
        print("compte ",accounts[j]," demande d'acceder au données\n")
        reseau_connect.envoi_au_contract({'from':accounts[j],'amount':5000000000000000000})

    print("l'envoi au contract est fait\n")
    print("envoie des 5 ether des differents compte a l'admin pour faire la demande d'acces")
    print("\n")

    for j in range(1,6):
        reseau_connect.envoi_vers_admin(accounts[0])
    print("\n")
    print("envoi des 5 ether de chaque compte vers l'admin")
    print("\n")

    # ce qui cest passer les comptes on fait la demande ( envoyer de lether)
    # l'ether vas au contract puis du contract vers le noued admin

    # maintenant il fait valider la demande ou la rejeter

    # avoire la valeur de confiance predefinis preedement 
    val_conf =[0,0,0,0,0,0]
    for i in range(1,6):
        val_conf[i]= reseau_connect.retourConf(accounts[i])
    print(val_conf)


    print("\n")
    print("envoi d'ether du compte admin vers les noueds qui on une valeur")
    print("de confiance plus grande que 5 ")
    print("admin vers le contract")
    for i in range (1,6):
        if(val_conf[i] >= 5):
            reseau_connect.envoi_au_contract({'from':accounts[0],'amount':100000000000000000})

    print("envoir de 0,1 ether")
    print("\ncontract vers noueds")

    for i in range(1,6):
        print("\ncontract vers noueds-----------",i)
        reseau_connect.jesaispas(accounts[i],val_conf[i])
    

def main():
    creation_noued()
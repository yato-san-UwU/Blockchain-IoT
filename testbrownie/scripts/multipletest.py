from multiprocessing.sharedctypes import Value
from os import access
from brownie import accounts, reseau, config
import random
import numpy as np
import matplotlib.pyplot as plt
from math import exp

def creation_noued():
    print("----- Creation des 4 noueds + du SP (admin)")
    print("le compte admin (SP) devrais avoir la premier addres " + str(accounts[0]))
    print("---------------------------------------------------")

    # l'admin  lui qui deploi les contract
    account= accounts[0]
    reseau_connect= reseau.deploy({"from":account})

    # ajoue du SP noued admin
    reseau_connect.addSP(accounts[0],'SP')


    val_noued1= list(np.arange(0,2.1,0.1))
    val_noued2= list(np.arange(0,2.1,0.1))
    val_noued3= list(np.arange(0,2.1,0.1))

    print("valeur conf noued 1",val_noued1)
    print("valeur conf noued 2",val_noued2)
    print("valeur conf noued 3",val_noued3)

    for boucle in range (0,21):
        #valeur de confiance au hasard pour 3 noueds
        noued1 = random.uniform(0,1)
        noueds1= round(noued1,2)
        #bonne valeur pour les 2 noueds malveillants au debut
        noued2_b = random.uniform(0,0.5)
        noueds2_b= round(noued2_b,2)
        noued3_b = random.uniform(0,0.4)
        noueds3_b= round(noued3_b,2)
        #valeur mauvaise pour les 2 noueds malveillants
        noued2_m = random.uniform(-1,0)
        noueds2_m= round(noued2_m,2)
        noued3_m = random.uniform(-1,0)    
        noueds3_m= round(noued3_m,2)


        #creation des 3 SC 
        reseau_connect.addNoueds(accounts[1],0 + 1,'SC'+str(1), noueds1)
        val_noued1[boucle]=noueds1
        #rajouter une conditions
        #au debut les noueds 2 et 3 davoir avoir de bonne valeur de confiance
        #puis ca ce degrade    

        #boucle pour le noueds 2
        if (boucle>=0 and boucle <8):
            #bonne valeur pour les noueds mauvais 
            reseau_connect.addNoueds(accounts[2],0 + 2,'SC'+str(2), noueds2_b)
            val_noued2[boucle]=noueds2_b
        elif(boucle>=8 and boucle<=16):
            #mauvaise valeur pour le noueds 2 entre 8 et 16emme transaction 
            reseau_connect.addNoueds(accounts[2],0 + 2,'SC'+str(2), noueds2_m)
            val_noued2[boucle]=noueds2_m
        elif(boucle>16):
            reseau_connect.addNoueds(accounts[2],0 + 2,'SC'+str(2), noueds2_b)
            val_noued2[boucle]=noueds2_b

        #boucle pour le noueds 3
        if (boucle>=0 and boucle <= 14):
            reseau_connect.addNoueds(accounts[3],0 + 3,'SC'+str(3), noueds3_b)
            val_noued3[boucle]=noueds3_b
        else :
            reseau_connect.addNoueds(accounts[3],0 + 3,'SC'+str(3), noueds3_m)
            val_noued3[boucle]=noueds3_m
        
        

        #transaction envoyer de lether des noueds vers ladmin pour demender un service
        #for j in range(1,4):
        #        if (accounts[j].balance() >= 10000000000000000000):
        #            transaction =[
        #                accounts[j].transfer(accounts[0], "0.05 ether", required_confs=0, silent=True)
        #            ]
        
        #10000000000000000000 = 10 ether
        #1000000000000000000  = 1 ether
        #100000000000000000   = 0.1 ether
        #10000000000000000    = 0.01 ether
                
        #transaction envoyer de lether en retour si la transaction est valide
        
#        for j in range(1,4):
#                if (accounts[0].balance() >=1000000000000000000):
#                    transaction=[
#                        accounts[0].transfer(accounts[j], "0.02 ether", required_confs=0, silent=True)
#                        ]
    
    print("valeur conf noued 1",val_noued1)
    print("valeur conf noued 2",val_noued2)
    print("valeur conf noued 3",val_noued3)
    print("\n")
#---------------------------------------- avoir les valeur avec gompert noueds 1
    
    # fct de veisselement
    I1= [0]*21
    for ageing in range(1,21):
        operator_one = 0.95 ** (21 - ageing)
        operator_two = val_noued1[ageing]
        I1[ageing] = I1[ageing - 1] + (operator_one * operator_two)



#---------------------------------------- avoir les valeur avec gompert noueds 2
    I2= [0]*21
    for ageing in range(1,21):
        operator_one_2 = 0.95 ** (21 - ageing)
        operator_two_2 = val_noued2[ageing]
        I2[ageing] = I2[ageing - 1] + (operator_one_2 * operator_two_2)


#---------------------------------------- avoir les valeur avec gompert noueds 3
    I3= [0]*21
    for ageing in range(1,21):
        operator_one_3 = 0.95 ** (21 - ageing)
        operator_two_3 = val_noued3[ageing]
        I3[ageing]=I3[ageing -1] + (operator_one_3 * operator_two_3)
    

#---------------------------------------- plot les resultat

    print(" I1 =",I1)
    print(" I2 =",I2)
    print(" I3 =",I3)

    x = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
    #x commun pour les 3

    y1= I1
    plt.plot(x,y1)
    plt.plot(x, y1, label = "noued1")

    y2= I2
    plt.plot(x,y2)    
    plt.plot(x, y2, label = "noued2")
    
    y3= I3
    plt.plot(x,y3)
    plt.plot(x, y3, label = "noued3")

    plt.xlabel('interaction')
    plt.ylabel('trust')
    plt.title("valeur de confiance de 3 noueds demandant l'acces au resource")

    plt.legend()
    plt.show()


def main():
    creation_noued()
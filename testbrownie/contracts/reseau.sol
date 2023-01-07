// SPDX-License-Identifier: MIT

pragma solidity >=0.4.0 <0.9.0;
pragma experimental ABIEncoderV2;


contract reseau {
    
    //------------------------------partie SP le noued principal------------------------------

    // structure du noued admin
    struct admin {
        uint256 IDadmin;
        string name;
    }

    mapping(address => admin) public SP;

    // fonction d'ajoue de l'admin
    function addSP(address add,string memory _name) public {
        SP[add].name= _name;
    }
    //------------------------------partie SP le noued principal------------------------------

    //------------------------------partie SC les differents noueds------------------------------

    // structure dun noued 
    struct noued {
        uint256 IDnoeud;
        string name;
        int val_conf;
    }

    mapping(address => noued ) public noueds;

    // ajouter un noueds (voir script python)
    function addNoueds(address add, uint256 _ID, string memory _name, int _val) public  {
        noueds[add].IDnoeud= _ID;
        noueds[add].name= _name;
        noueds[add].val_conf= _val;
    }
    // retounrer le nom du SP
    function retourNomSp(address _add) public view returns(string memory){
        return noueds[_add].name;
    }    
    // retourner la valeur de confiance 
    function retourConf(address _add)public view returns(int) {
        return noueds[_add].val_conf;
    }

    //------------------------------partie SC les differents noueds------------------------------

    //------------------------------communication des noueds-------------------------------------


    // envoi de ether appartir dun compte sur le contract general 
    function envoi_au_contract() external payable{
    }

    // puis du contract vers l'admin
    function envoi_vers_admin(address payable addr) public{
        addr.transfer(5000000000000000000);    
    }


    // de contract vers le noueds
    function envoi_vers_noueds(address payable ads) public {
        ads.transfer(100000000000000000);
    }

    function jesaispas(address payable _add, uint256 val_conf) public{
            if(val_conf >= 5){
                envoi_vers_noueds(_add);
            }
    }
}
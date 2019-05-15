/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package me.osc3b.csgoleds;

/**
 *
 * @author Oscar
 */

//import com.brekcel.csgostate.JSON.Weapon;
import com.brekcel.csgostate.post.PostHandlerAdapter;

public class CSGOVariables extends PostHandlerAdapter {
    
    int killsguardadas = 0;
    String teamAct = "NULL";
    //int porcentajeCargador = 0;
    
    @Override
    public void playerHealthChange(int health) { 
        System.out.println(" % La vida del jugador a cambiado a: " + health);
        CSGOLeds.arduino.serialWrite(Integer.toString(health+500));
    }

    @Override
    public void playerMatchKillsChange(int kills) {
        System.out.println("***** Nueva kill. Kills: " + kills + " *****");
        if(kills > killsguardadas){
            CSGOLeds.arduino.serialWrite('1');
            killsguardadas = kills;
        }
    }
    
    @Override
    public void playerFlashedChange(int flashed){
        System.out.println("***** FLASHED " + flashed + "******");
        if(flashed >= 150) //De 0 a 255
            CSGOLeds.arduino.serialWrite('2');
    }
    
    /*@Override
    public void roundReset(){
        System.out.println("======================================\n Nueva ronda \n==============================================");
        killsguardadas = 0;
    }*/
    
    @Override
    public void playerTeamChange(String team){
        teamAct = team;
        killsguardadas = 0;
    }
    
    @Override
    public void roundWinningTeamChange(String team){
        if(team.equals(teamAct)){
            System.out.println("RONDA GANADA\n");
            CSGOLeds.arduino.serialWrite('3');
        }else{
            System.out.println("RONDA PERDIDA\n");
            CSGOLeds.arduino.serialWrite('4');
        }
    }
    
    @Override
    public void bombPlanted(){
        System.out.println("BOMBA PLANTADA");
        CSGOLeds.arduino.serialWrite('5');
    }
    
    @Override
    public void bombExploded(){
        System.out.println("LA BOMBA HA EXPLOTADO");
        CSGOLeds.arduino.serialWrite('6');
    }
    
    @Override
    public void bombDefused(){
        System.out.println("BOMBA DESMONTADA");
        CSGOLeds.arduino.serialWrite('7');
    }
    
    /*@Override
    public void weaponActiveChange(Weapon weapon){
        System.out.println("Arma cambiada a: " + weapon.getName());
        System.out.println("(C) Balas en el cargador: " + weapon.getAmmoClip() + "/" + weapon.getAmmoClipMax());
        porcentajeCargador = round((float)(weapon.getAmmoClip()*100)/weapon.getAmmoClipMax());
        //Envia primero 0% balas durante 100ms ya que cambia de arma, luego el % cargador
        CSGOLeds.arduino.serialWrite(Integer.toString(300)+Integer.toString(porcentajeCargador+300), 3, 100);
    }
    
    @Override
    public void weaponShoot(Weapon weapon){
        System.out.println("(S) Balas en el cargador: " + weapon.getAmmoClip() + "/" + weapon.getAmmoClipMax());
        porcentajeCargador = round((float)(weapon.getAmmoClip()*100)/weapon.getAmmoClipMax());
        CSGOLeds.arduino.serialWrite(Integer.toString(porcentajeCargador+300));
    }
    
    @Override
    public void weaponReload(Weapon weapon){
        System.out.println("(R) Balas en el cargador: " + weapon.getAmmoClip() + "/" + weapon.getAmmoClipMax());
        porcentajeCargador = 100;
        CSGOLeds.arduino.serialWrite(Integer.toString(400));
    }*/
}


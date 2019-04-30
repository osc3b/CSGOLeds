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

import com.brekcel.csgostate.post.PostHandlerAdapter;

public class CSGOVariables extends PostHandlerAdapter {
    
    int killsguardadas = 0;
    String teamAct = "NULL";
    
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
        System.out.println("***** FLASHED ******");
        CSGOLeds.arduino.serialWrite('2');
    }
    
    @Override
    public void roundChange(int round){
        System.out.println("======================================\n Nueva ronda \n==============================================");
    }
    
    @Override
    public void playerTeamChange(String team){
        teamAct = team;
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
}

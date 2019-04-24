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
import com.brekcel.csgostate.JSON.*;

public class CSGOVariables extends PostHandlerAdapter {
    @Override
    public void playerHealthChange(int health) { 
        System.out.println(" % La vida del jugador a cambiado a: " + health);
        CSGOLeds.arduino.serialWrite(Integer.toString(health+500));
    }

    @Override
    public void playerMatchKillsChange(int kills) {
        System.out.println("***** Nueva kill. Kills: " + kills + " *****");
        CSGOLeds.arduino.serialWrite('1');
    }
    
    @Override
    public void playerFlashedChange(int flashed){
        System.out.println("***** FLASHED ******");
        CSGOLeds.arduino.serialWrite('2');
    }
    
    @Override
    public void newRound(Round round){
        System.out.println("======================================\n Nueva ronda \n==============================================");
    }
}

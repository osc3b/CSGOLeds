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
import java.util.logging.Level;
import java.util.logging.Logger;
import com.brekcel.csgostate.JSON.*;

public class CSGOVariables extends PostHandlerAdapter {
    @Override
    public void playerHealthChange(int health) { 
        System.out.println(" % La vida del jugador a cambiado a: " + health);
        try {
            CSGOLeds.arduino.sendData(Integer.toString(health+500));
        } catch (ArduinoException | SerialPortException ex) {
            Logger.getLogger(CSGOVariables.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void playerMatchKillsChange(int kills) {
        System.out.println("***** Nueva kill. Kills: " + kills + " *****");
        try {
            CSGOLeds.arduino.sendData("1");
        } catch (ArduinoException | SerialPortException ex) {
            Logger.getLogger(CSGOVariables.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void playerFlashedChange(int flashed){
        System.out.println("***** FLASHED ******");
        try {
            CSGOLeds.arduino.sendData("2");
        } catch (ArduinoException | SerialPortException ex) {
            Logger.getLogger(CSGOVariables.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void newRound(Round round){
        System.out.println("======================================\n Nueva ronda \n==============================================");
    }
}

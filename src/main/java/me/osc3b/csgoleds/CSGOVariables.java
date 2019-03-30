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
import com.panamahitek.ArduinoException;
import java.util.logging.Level;
import java.util.logging.Logger;
import jssc.SerialPortException;

public class CSGOVariables extends PostHandlerAdapter {
	@Override
	public void playerHealthChange(int health) { 
    	System.out.println("AHORA LA VIDA DEL JUGADOR EEEEEEEEEEEEEEEEESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS: " + health);
    }
        
        public void playerMatchKillsChange(int kills) {
            System.out.println("======================================\nNUEVA KILLLLL. Kills: " + kills + "\n==============================================");
            try {
                CSGOLeds.arduino.sendData("2");
            } catch (ArduinoException | SerialPortException ex) {
                Logger.getLogger(CSGOVariables.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
}

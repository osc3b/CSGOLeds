
package me.osc3b.csgoleds;
import java.util.logging.Level;
import java.util.logging.Logger;
import com.brekcel.csgostate.*;
import java.io.IOException;
import arduino.*;

/**
 *
 * @author osc3b
 */
public class CSGOLeds {
    static Arduino arduino = new Arduino("COM3", 500000);
    boolean ejecutando = true;
    static Server server;
    
    public CSGOLeds(){
        if(arduino.openConnection()){
            Logger.getLogger(CSGOLeds.class.getName()).log(Level.INFO, null, "Arduino conectada correctamente");
            System.out.println("Arduino conectada correctamente");
        }
        try {
            Thread.sleep(2500);
        } catch (InterruptedException ex) {
            Logger.getLogger(CSGOLeds.class.getName()).log(Level.SEVERE, null, ex);
        }
        //arduino.serialWrite("1"); //Envia inicialización al Arduino
    }
    
    public static void main(String[] args) throws IOException {
        CSGOLeds main = new CSGOLeds();
        CSGOVariables csgo = new CSGOVariables();
        server = new Server(1338, csgo, true);
        while(main.ejecutando){
            //TODO Comprobaciones del juego
            //int vida = server.getCurrentJSR().getPlayer().getState().getHealth();
            //System.out.println("AHORA LA VIDA DEL JUGADOR ES: " + vida);
        }
    }
}

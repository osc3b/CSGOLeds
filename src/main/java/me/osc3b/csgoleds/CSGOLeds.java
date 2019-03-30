
package me.osc3b.csgoleds;
import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_Arduino;
import java.util.logging.Level;
import java.util.logging.Logger;
import jssc.SerialPortException;

/**
 *
 * @author osc3b
 */
public class CSGOLeds {
    PanamaHitek_Arduino arduino = new PanamaHitek_Arduino();
    boolean ejecutando = true;
    
    public CSGOLeds(){
        conectarArduino();
        Logger.getLogger(CSGOLeds.class.getName()).log(Level.INFO, null, "Arduino conectada correctamente");
        try {
            Thread.sleep(2500);
        } catch (InterruptedException ex) {
            Logger.getLogger(CSGOLeds.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            arduino.sendData("1"); //Envia inicialización al Arduino
        } catch (ArduinoException | SerialPortException ex) {
            Logger.getLogger(CSGOLeds.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void conectarArduino(){
        try {
            arduino.arduinoTX("COM3", 1000000); //Conecta al COM3 con un serial rate de 1000000
        } catch (ArduinoException ex) {
            Logger.getLogger(CSGOLeds.class.getName()).log(Level.SEVERE, null, ex);
            System.exit(1);
        }
    }
    
    public static void main(String[] args) {
        CSGOLeds main = new CSGOLeds();
        //while(main.ejecutando){
        //TODO Comprobaciones del juego
        //}
    }
}

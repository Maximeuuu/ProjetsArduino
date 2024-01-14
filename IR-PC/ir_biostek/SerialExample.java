import javax.comm.*;

public class SerialExample {
    public static void main(String[] args) throws Exception {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier("COM9");
        SerialPort serialPort = (SerialPort) portIdentifier.open("SerialExample", 9600); //1000

        // Utilisez la classe SerialPort pour configurer et interagir avec le port série

        serialPort.close();
    }
}

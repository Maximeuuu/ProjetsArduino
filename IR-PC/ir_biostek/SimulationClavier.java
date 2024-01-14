import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class SimulationClavier extends JFrame implements KeyListener {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimulationClavier simulationClavier = new SimulationClavier();
            simulationClavier.createAndShowGUI();
        });
    }

    public SimulationClavier() {
        super("Simulation Clavier");
    }

    private void createAndShowGUI() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addKeyListener(this);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
        requestFocus();
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        System.out.println("Code de la touche : " + keyCode);
    }

    @Override
    public void keyReleased(KeyEvent e) {
        // Ne rien faire lors de la libération de la touche
    }

    @Override
    public void keyTyped(KeyEvent e) {
        // Ne rien faire lors de la frappe d'une touche
    }
}

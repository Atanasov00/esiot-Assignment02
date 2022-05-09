package scm_gui;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.*;

public class GUI extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6956878900594680800L;

	public GUI() {
		
		final JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setSize(450,450);
		frame.setTitle("Coffee Machine Manager");
		
		final BorderLayout border = new BorderLayout();
		
		final JPanel panel = new JPanel();
		final JPanel panel2 = new JPanel(new FlowLayout());
		final JPanel panel3 = new JPanel(new GridLayout(3,1));
		final JButton refillButton = new JButton("Refill");
		final JButton recoverButton = new JButton("Recover");
		
		final JLabel modalityLabel = new JLabel("Modality:");
		final JLabel productsLabel = new JLabel("Products available:");
		final JLabel selftestLabel = new JLabel("Self-test performed:");
		
		final JLabel title = new JLabel("Coffee Machine Manager", JLabel.CENTER);
		title.setFont(new Font("Serif", Font.BOLD, 20));
		
		panel.setLayout(border);
		frame.getContentPane().add(panel);
		
		panel2.add(refillButton);
		panel2.add(recoverButton);
		
		panel3.add(modalityLabel);
		panel3.add(productsLabel);
		panel3.add(selftestLabel);
		
		panel.add(panel2, BorderLayout.SOUTH);
		panel.add(panel3, BorderLayout.CENTER);
		panel.add(title, BorderLayout.NORTH);
		
		frame.setVisible(true);
	}
	
}

package scm_gui;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class GUI extends JFrame {

	/**
	 *
	 */
	private static final long serialVersionUID = 6956878900594680800L;

	private final JButton refillButton = new JButton("Refill");
	private final JButton recoverButton = new JButton("Recover");

	private final JLabel modalityLabel = new JLabel("Modality:");
	private final JLabel coffeeAvailable = new JLabel("Coffee available:");
	private final JLabel chocolateAvailable = new JLabel("Chocolate available:");
	private final JLabel teaAvailable = new JLabel("Tea available:");
	private final JLabel selftestLabel = new JLabel("Self-test performed:");


	public GUI() {

		final JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setSize(450,450);
		frame.setTitle("Coffee Machine Manager");

		final BorderLayout border = new BorderLayout();

		final JPanel panel = new JPanel();
		final JPanel panel2 = new JPanel(new FlowLayout());
		final JPanel panel3 = new JPanel(new GridLayout(5,1));

		final JLabel title = new JLabel("Coffee Machine Manager", JLabel.CENTER);
		title.setFont(new Font("Serif", Font.BOLD, 20));

		panel.setLayout(border);
		frame.getContentPane().add(panel);

		refillButton.setEnabled(false);
		recoverButton.setEnabled(false);

		panel2.add(refillButton);
		panel2.add(recoverButton);

		panel3.add(modalityLabel);
		panel3.add(coffeeAvailable);
		panel3.add(chocolateAvailable);
		panel3.add(teaAvailable);
		panel3.add(selftestLabel);

		panel.add(panel2, BorderLayout.SOUTH);
		panel.add(panel3, BorderLayout.CENTER);
		panel.add(title, BorderLayout.NORTH);

		frame.setVisible(true);
	}

	public void registerController(Controller contr){
		refillButton.addActionListener(contr);
		recoverButton.addActionListener(contr);
	}

	public void setModalityInfo(String msg) {
		SwingUtilities.invokeLater(() -> {
			modalityLabel.setText(msg);
		});
	}

	public void setCoffeeInfo(String msg) {
		SwingUtilities.invokeLater(() -> {
			coffeeAvailable.setText(msg);
		});
	}

	public void setChocolateInfo(String msg) {
		SwingUtilities.invokeLater(() -> {
			chocolateAvailable.setText(msg);
		});
	}

	public void setTeaInfo(String msg) {
		SwingUtilities.invokeLater(() -> {
			teaAvailable.setText(msg);
		});
	}

	public void setSelftestInfo(String msg) {
		SwingUtilities.invokeLater(() -> {
			selftestLabel.setText(msg);
		});
	}

	public void startEmptyMaintenance() {
		SwingUtilities.invokeLater(() -> {
			refillButton.setEnabled(true);
		});
	}

	public void startTempMaintenance() {
		SwingUtilities.invokeLater(() -> {
			recoverButton.setEnabled(true);
		});
	}

	public void refilled(){
		SwingUtilities.invokeLater(() -> {
			refillButton.setEnabled(false);
		});
	}

	public void recovered() {
		SwingUtilities.invokeLater(() -> {
			recoverButton.setEnabled(false);
		});
	}
}

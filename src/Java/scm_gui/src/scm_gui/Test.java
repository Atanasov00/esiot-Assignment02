package scm_gui;

import jssc.*;
import javax.swing.SwingUtilities;

public class Test {

	private static GUI view = null;
	private static LogView logger = null;
	
	public static void main(String[] args) throws Exception {
		
		SwingUtilities.invokeAndWait(() -> {
			view = new GUI();
			logger = new LogView();
		});
		
		String portName = SerialPortList.getPortNames()[0];
		//System.out.println(portName);
		Controller contr = new Controller(portName, view, logger);
		view.registerController(contr);
	}
}

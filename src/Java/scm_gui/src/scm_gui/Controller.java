package scm_gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import SerialCommChannel.SerialCommChannel;

public class Controller implements ActionListener {

	SerialCommChannel channel;
	GUI view;

	public Controller(String port, GUI view, LogView logger) throws Exception {
		this.view = view;
		channel = new SerialCommChannel(port, 9600);
		new MonitoringAgent(channel,view,logger).start();

		System.out.println("Waiting arduino for rebootin...");
		Thread.sleep(4000);
		System.out.println("Ready");
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			if(e.getActionCommand().equals("Refill")) {
					channel.sendMsg("10");
			} else if(e.getActionCommand().equals("Recover")) {
				channel.sendMsg("Start recovering...");
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}



}

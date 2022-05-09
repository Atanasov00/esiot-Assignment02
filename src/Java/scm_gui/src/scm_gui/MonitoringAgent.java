package scm_gui;

import SerialCommChannel.SerialCommChannel;

public class MonitoringAgent extends Thread {

	private final SerialCommChannel channel;
	private final GUI view;
	private final LogView logger;

	private int coffeeQuantity;
	private int chocolateQuantity;
	private int teaQuantity;
	private int selftestPerformed;

	static final int QUANTITY = 10;
	static final String CM_PREFIX 	=  "cm:";
	static final String IDLE_PREFIX = "dl";
	static final String WORKING_PREFIX = "wk";
	static final String ASSISTANCE_PREFIX = "ss";
	static final String COFFEEQ_PREFIX = "cfq";
	static final String CHOCOLATEQ_PREFIX = "chq";
	static final String TEAQ_PREFIX = "teq";
	static final String SELF_PREFIX = "sf";
	static final String MSG_REFILLED  = "rf";
	static final String MSG_RECOVERED = "rd";
	static final String MSG_ASSISTANCE_EMPTY = "em";
	static final String MSG_ASSISTANCE_TEMP = "tm";



	public MonitoringAgent(SerialCommChannel channel, GUI view, LogView logger) {
		this.channel = channel;
		this.view = view;
		this.logger = logger;
		coffeeQuantity = QUANTITY;
		chocolateQuantity = QUANTITY;
		teaQuantity = QUANTITY;
		selftestPerformed = 0;
	}

	@Override
	public void run() {
		while(true) {
			try {
				if(channel.isMsgAvailable()) {
					String msg = channel.receiveMsg();
					if(msg.startsWith(CM_PREFIX)) {
						String cmd = msg.substring(CM_PREFIX.length());
						logger.log("new command: "+cmd);
						if(cmd.startsWith(IDLE_PREFIX)) {
							view.setModalityInfo("Modality: IDLE");
						} else if(cmd.startsWith(WORKING_PREFIX)) {
							view.setModalityInfo("Modality: WORKING");
						} else if(cmd.startsWith(ASSISTANCE_PREFIX)) {
							view.setModalityInfo("Modality: ASSISTANCE");
						} else if(cmd.startsWith(COFFEEQ_PREFIX)) {
							cmd = msg.substring(COFFEEQ_PREFIX.length());
							view.setCoffeeInfo("Coffee available: " + cmd);
						} else if(cmd.startsWith(CHOCOLATEQ_PREFIX)) {
							cmd = msg.substring(CHOCOLATEQ_PREFIX.length());
							view.setChocolateInfo("Chocolate available: " + cmd);
						} else if(cmd.startsWith(CHOCOLATEQ_PREFIX)) {
							cmd = msg.substring(TEAQ_PREFIX.length());
							view.setTeaInfo("Tea available: " + cmd);
						} else if(cmd.startsWith(SELF_PREFIX)) {
							view.setSelftestInfo("Selftest performed: " + selftestPerformed);
						} else if(cmd.startsWith(MSG_ASSISTANCE_EMPTY)) {
							view.startEmptyMaintenance();
						} else if(cmd.startsWith(MSG_ASSISTANCE_TEMP)) {
							view.startTempMaintenance();
						}
					}
				}
				} catch(Exception ex) {
					ex.printStackTrace();
				}
			}
	}
}

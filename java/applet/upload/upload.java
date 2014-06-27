//public class UploadApplet { //.java

// http post example: http://stackoverflow.com/questions/2469451/upload-files-with-java

import java.io.*;
import java.awt.*; 
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;
import javax.swing.border.*;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.nio.file.WatchEvent.Kind;

public class upload extends JApplet
implements ActionListener {
	private JPanel pane = null;
	private JScrollPane scrolling = null;
	private JTextPane fileBox = null;
	private JTextField tfFilename = null;
	private JButton butLoad = null;
	private final String LOAD = "load";
	
	public static String UploadFile = "";

	private String file = "";
	private String target = "";
	private String method = "";
	private String dir = "";
	private DirectoryWatcher d;
	private Path watch;
    
	public void init() {
		// read parameter data
    	this.file   = getStrParam( "file",   file);
    	this.target = getStrParam( "target", target);
    	this.method = getStrParam( "method", method); 
    	this.dir    = getStrParam( "dir",    dir);
    	System.out.println("param dir: " + this.dir);
    	
		try {
			jbInit();
		} catch(Exception e) {
			e.printStackTrace();
		}

    	this.watch = Paths.get(this.dir);
    	this.d = new DirectoryWatcher(this.watch);
	}

	// method which will read data from file, and return it in
	// String
	public String readFile(String fn) {
		String thisLine, ret = "";
		try {
			FileInputStream fin =  new FileInputStream(fn);
			BufferedReader myInput = new BufferedReader
					(new InputStreamReader(fin));
			while ((thisLine = myInput.readLine()) != null) {  
				ret += thisLine + "\n";
			}
		} catch (Exception e) {
			ret = "Cannot load, exception!";
		}
		return ret;
	}

	private void jbInit() throws Exception {
		pane = new JPanel();
		pane.setBounds(new Rectangle(0, 0, 500, 325));
		pane.setLayout(null);
		pane.setBorder(BorderFactory.createEtchedBorder(
				EtchedBorder.LOWERED));
		pane.setBackground(new Color(221, 194, 219));

		fileBox = new JTextPane();
		fileBox.setText("...");
		fileBox.setEditable(false);
		scrolling = new JScrollPane(fileBox);
		scrolling.setBounds(new Rectangle(16, 65, 295, 225));

		tfFilename = new JTextField();
		tfFilename.setText(this.dir);
		tfFilename.setBounds(new Rectangle(16, 23, 206, 29));

		butLoad = new JButton();
		butLoad.setBounds(new Rectangle(231, 23, 80, 30));
		butLoad.setText("Poll");
		butLoad.setActionCommand(LOAD);
		butLoad.addActionListener(this);

		pane.add(scrolling);
		pane.add(tfFilename);
		pane.add(butLoad);
		
		setContentPane(pane);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals(LOAD)) {
			System.out.println("Starting thread ...");
			// fileBox.setText(readFile(tfFilename.getText()));
			//this.d.run();
			
			//System.out.println(this.watch.getFileName());
			//Path pathToWatch = FileSystems.getDefault().getPath("/home/wus/tmp");
			DirectoryWatcher dirWatcher = new DirectoryWatcher(this.watch);
			Thread dirWatcherThread = new Thread(dirWatcher);
			dirWatcherThread.start();

			// interrupt the program after 10 seconds to stop it.
			try {
				//Thread.sleep(300000); // 5 minutes, 300 seconds
				//dirWatcherThread.start();
				dirWatcherThread.join();
				dirWatcherThread.interrupt();
			} catch (InterruptedException ex) {
				System.out.println("interrupted. Goodbye");
				// TODO: shut down applet, emit live script event or info, maybe reaload or close
				//return;
			}
			
			System.out.println("File to upload: " + UploadFile.toString());
		}
	}
	
	private String getStrParam( String name, String defaultVal ) {
		String param = this.getParameter(name);
		if (param != null)
			return param;
		return defaultVal;
	}
}


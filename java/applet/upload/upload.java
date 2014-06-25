//public class UploadApplet { //.java
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

public class upload extends JApplet
implements ActionListener {
	private JPanel pane = null;
	private JScrollPane scrolling = null;
	private JTextPane fileBox = null;
	private JTextField tfFilename = null;
	private JButton butLoad = null;
	private final String LOAD = "load";

	private String file = "";
    private String target = "";
    private String method = "";
    private String dir = "";
    //private DirectoryWatcher d;
    Path watch;
    
	public void init() {
		// read parameter data
    	file   = getStrParam( "file",   file);
    	target = getStrParam( "target", target);
    	method = getStrParam( "method", method); 
    	dir    = getStrParam( "dir",    dir);
    	
		try {
			jbInit();
		} catch(Exception e) {
			e.printStackTrace();
		}

    	Path watch = Paths.get("/home/wus/tmp");
    	//this.d = new DirectoryWatcher(watch, fileBox);
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
		fileBox.setText("");
		fileBox.setEditable(false);
		scrolling = new JScrollPane(fileBox);
		scrolling.setBounds(new Rectangle(16, 65, 295, 225));

		tfFilename = new JTextField();
		tfFilename.setText(dir);
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
			// fileBox.setText(readFile(tfFilename.getText()));
			//this.d.run();
			
			try {
				WatchService watchService = watch.getFileSystem().newWatchService();
				watch.register(watchService, StandardWatchEventKinds.ENTRY_CREATE,
						StandardWatchEventKinds.ENTRY_MODIFY,
						StandardWatchEventKinds.ENTRY_DELETE);
	
				// loop forever to watch directory
				while (true) {
					WatchKey watchKey;
					watchKey = watchService.take(); // this call is blocking until
					// events are present
	
					// poll for file system events on the WatchKey
					for (final WatchEvent<?> event : watchKey.pollEvents()) {
						//printEvent(event);
						;
					}
	
					// if the watched directed gets deleted, get out of run method
					if (!watchKey.reset()) {
						System.out.println("No longer valid");
						watchKey.cancel();
						watchService.close();
						break;
					}
				}

			} catch (InterruptedException ex) {
				System.out.println("interrupted. Goodbye");
				return;
			} catch (IOException ex) {
				ex.printStackTrace(); // don't do this in production code. Use a
				// loggin framework
				return;
			}


		}
	}
	
    private String getStrParam( String name, String defaultVal ) {
		String param = this.getParameter(name);
		if (param != null)
			return param;
		return defaultVal;
    }
}

/*
   private String file = "";
    private String target = "";
    private String method = "";
    private String dir = "";
    
	public void init() {
    	super.init();
    	
		// read parameter data
    	file   = getStrParam( "file",   file);
    	target = getStrParam( "target", target);
    	//method = getStrParam( "method", method); 
    	//dir    = getStrParam( "dir",    dir);
    	
    	try {
			jbInit();
		} catch(Exception e) {
			e.printStackTrace();
		}
    	/ *
    	Path watch = Paths.get("/tmp");
    	DirectoryWatcher d = new DirectoryWatcher(watch);
    	* /
	}

    private String getStrParam( String name, String defaultVal ) {
		String param = this.getParameter(name);
		if (param != null)
			return param;
		return defaultVal;
    }
*/

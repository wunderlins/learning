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

import netscape.javascript.*;
//import netscape.javascript.JSObject;

public class upload extends JApplet
implements ActionListener {
	private JPanel pane = null;
	private JScrollPane scrolling = null;
	private JTextPane fileBox = null;
	private JTextField tfFilename = null;
	private JButton butLoad = null;
	private final String LOAD = "load";
	
	private String method = "";
	private String formFieldName = "uploadedFile";
	private DirectoryWatcher d;
	private Path watch;
	
	private JSObject window;
	
	public static long fileSize;
	public String dir = "";
	public String target = "";
	public static String UploadFile = "";
	public int status = 0;
	public String[] statusName = new String[20];
	public static int statusCode = 0;
	public static String mimeType = "";

    
	public void init() {
		
		this.statusName[0] = "Unknown";
		this.statusName[1] = "Initializing";
		this.statusName[2] = "Polling";
		this.statusName[3] = "Found File";
		this.statusName[4] = "Uploading";
		this.statusName[5] = "Finished";
		
    	this.window = JSObject.getWindow(this);
    	
		this.status = 1;
		this.window.eval("appletStatusChange()");
		/**
		 * the following parameters should be user configurable:
		 *   dir: the directory to poll
		 *   fieldname: form field name used in post
		 *   target: http url of server-side script
		 *   userparam: name=value|name1=value pairs which the user might 
		 *              want to pass along with the uploaded file, things like 
		 *              authentication tokens, session id's etc.
		 * 
		 * The following attributes shall be available to javascript:
		 *   int status: 0: init, 1: polling, 2: found file, 3: found file, 4: uploading, 5: finished
		 *   int serverResponseCode: http response code
		 *   int fileSize (bytes)
		 *   String: mimeType
		 *   int progress (0-100), only updated during upload.
		 */
		
		// read parameter data
    	this.target = getStrParam( "target", target);
    	this.method = getStrParam( "method", method); 
    	this.dir    = getStrParam( "dir",    dir);
    	this.formFieldName = getStrParam("name", formFieldName);
    	System.out.println("param dir: " + this.dir);
    	
    	/*
		try {
			jbInit();
		} catch(Exception e) {
			e.printStackTrace();
		}
		*/
    	
		pane = new JPanel();
		setContentPane(pane);
		
    	this.watch = Paths.get(this.dir);
    	this.d = new DirectoryWatcher(this.watch);
		this.status = 2;
		this.window.eval("appletStatusChange()");
		this.window.eval("appletInit()");
    	
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
			this.status = 3;
			this.window.eval("appletStatusChange()");
		} catch (InterruptedException ex) {
			System.out.println("interrupted. Goodbye");
			// TODO: shut down applet, emit live script event or info, maybe reaload or close
			//return;
		}
		
		System.out.println("File to upload: " + UploadFile.toString());
		this.window.eval("appletGotFile()");
		
		try {
			PostFile conn = new PostFile();
			this.status = 4;
			this.window.eval("appletStatusChange()");
			conn.main(this.target, 
					  this.dir + "/" + UploadFile.toString(), 
					  this.formFieldName);
			// TODO: check response status, must make sure the whole file was accepted
			
			this.status = 5;
			this.window.eval("appletStatusChange()");
			this.window.eval("appletFinished()");
			/*
			if (num.intValue() != 5) {
				throw new RuntimeException(); // test failed
			} */
			
		} catch (Exception ex) {
			System.out.println("Failed uploading, " + ex.toString());
			ex.printStackTrace();
			this.window.eval("appletFailed()");
		}
    	
	}
	
	/*
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
	*/

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
		
		try {
			PostFile conn = new PostFile();
			conn.main(this.target, this.dir + "/" + UploadFile.toString(), this.formFieldName);
			// TODO: check response status, must make sure the whole file was accepted
			
			this.window.eval("applietFinished()");
			/*
			if (num.intValue() != 5) {
				throw new RuntimeException(); // test failed
			} */
			
		} catch (Exception ex) {
			System.out.println("Failed uploading, " + ex.toString());
			ex.printStackTrace();
		}
	}
	
	private String getStrParam( String name, String defaultVal ) {
		String param = this.getParameter(name);
		if (param != null) {
			System.out.println("Parameter " + name + " Found: " + param);
			return param;
		}
		System.out.println("Parameter " + name + " not Found, using default value " + defaultVal);
		return defaultVal;
	}
}


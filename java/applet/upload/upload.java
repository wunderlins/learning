/**
 * upload utility
 * 
 * goal:
 *   1 poll directory
 *   2 read file
 *   3 upload to server
 *   4 javascript (livescript?) API
 * 
 * Tutorial:
 * http://www.developer.com/java/other/article.php/3303561/Creating-a-Trusted-Applet-with-Local-File-System-Access-Rights.htm
 */

import java.io.*;

/*
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.nio.file.WatchEvent.Kind;
*/

import java.awt.*; 
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;
import javax.swing.border.*;

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
    
	public void init() {
    	super.init();

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
	}

    private String getStrParam( String name, String defaultVal ) {
		String param = this.getParameter(name);
		if (param != null)
			return param;
		return defaultVal;
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
		/*
		Path pathToWatch = FileSystems.getDefault().getPath("/tmp/java7");
		DirectoryWatcher dirWatcher = new DirectoryWatcher(pathToWatch);
		Thread dirWatcherThread = new Thread(dirWatcher);
		dirWatcherThread.start();

		// interrupt the program after 10 seconds to stop it.
		Thread.sleep(10000);
		dirWatcherThread.interrupt();
		*/
		
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
		tfFilename.setText(file);
		tfFilename.setBounds(new Rectangle(16, 23, 206, 29));

		butLoad = new JButton();
		butLoad.setBounds(new Rectangle(231, 23, 80, 30));
		butLoad.setText("Load");
		butLoad.setActionCommand(LOAD);
		butLoad.addActionListener(this);

		pane.add(scrolling);
		pane.add(tfFilename);
		pane.add(butLoad);
		
//        "dir: "+dir + "\n" +
		String info = "file: "+file + "\n" +
	                  "target: "+target + "\n" +
		              "method: "+method + "\n===================\n\n";
		fileBox.setText(info);
		setContentPane(pane);
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals(LOAD)) {
			fileBox.setText(readFile(tfFilename.getText()));
		}
	}

	/*
	private Path path;
	
	/ *
	public DirectoryWatcher(Path path) {
		this.path = path;
	}
	* /

	// print the events and the affected file
	private void printEvent(WatchEvent<?> event) {
		Kind<?> kind = event.kind();
		if (kind.equals(StandardWatchEventKinds.ENTRY_CREATE)) {
			Path pathCreated = (Path) event.context();
			System.out.println("Entry created:" + pathCreated);
			//fileBox.setText("Entry created:" + pathCreated);
		} else if (kind.equals(StandardWatchEventKinds.ENTRY_DELETE)) {
			Path pathDeleted = (Path) event.context();
			System.out.println("Entry deleted:" + pathDeleted);
			//fileBox.setText("Entry deleted:" + pathDeleted);
		} else if (kind.equals(StandardWatchEventKinds.ENTRY_MODIFY)) {
			Path pathModified = (Path) event.context();
			System.out.println("Entry modified:" + pathModified);
			//fileBox.setText("Entry modified:" + pathModified);
		}
	}

	@Override
	public void run() {
		try {
			WatchService watchService = path.getFileSystem().newWatchService();
			path.register(watchService, StandardWatchEventKinds.ENTRY_CREATE,
					StandardWatchEventKinds.ENTRY_MODIFY,
					StandardWatchEventKinds.ENTRY_DELETE);

			// loop forever to watch directory
			while (true) {
				WatchKey watchKey;
				watchKey = watchService.take(); // this call is blocking until
				// events are present

				// poll for file system events on the WatchKey
				for (final WatchEvent<?> event : watchKey.pollEvents()) {
					printEvent(event);
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
	*/
}

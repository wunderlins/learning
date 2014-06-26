//package com.markusjais;

import java.io.IOException;
import java.io.File;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchEvent.Kind;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;

import javax.swing.JTextField;
import javax.swing.JTextPane;

// Simple class to watch directory events.
class DirectoryWatcher implements Runnable {

	private Path path;
	private Path observedFile = null;

	public DirectoryWatcher(Path path) {
		this.path = path;
		//this.fileBox = fileBox;
	}

	// print the events and the affected file
	private void printEvent(WatchEvent<?> event) {
		Kind<?> kind = event.kind();
		if (kind.equals(StandardWatchEventKinds.ENTRY_CREATE)) {
			Path pathCreated = (Path) event.context();
			if(this.observedFile == null) {
				this.observedFile = pathCreated; 
				System.out.println("Entry created:" + pathCreated + " " + event.count() + this.observedFile.toString());
			}
			//this.fileBox.setText("Entry created:" + pathCreated);
			//String buf = this.fileBox.getText();
			//buf.concat("Entry created:" + pathCreated);
			//this.fileBox.setText("...----------");
		} else if (kind.equals(StandardWatchEventKinds.ENTRY_DELETE)) {
			Path pathDeleted = (Path) event.context();
			System.out.println("Entry deleted:" + pathDeleted + " " + event.count());
			
		} else if (kind.equals(StandardWatchEventKinds.ENTRY_MODIFY)) {
			Path pathModified = (Path) event.context();
			File f = new File(pathModified.toString());
			System.out.println("Entry modified:" + pathModified + " " + event.count() + " " + f.length());
		}
	}

	@Override
	public void run() {
		long size = 0;
		int retry = 3; // TODO: check if 3 retries à 200ms is enough
		
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
				
				if (this.observedFile != null) {
					while (true) {
						File f = new File(this.path + "/" + this.observedFile.toString());
						System.out.println("Observing:" + this.observedFile.toString() + " " + f.length());
						Thread.currentThread().sleep(200);
						
						if (f.length() > 0) {
							if (size != f.length()) {
								size = f.length();
								retry = 3;
							} else {
								retry--;
								if (retry == 0)
									break;
							}
						}
						
						//System.out.println("End of loop");
					}
					
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
		
		// TODO: if we got this far, our file is ready for uploading.
		System.out.println("Done writing, " + this.observedFile.toString() + ", bytes: " + size);
		
	}
}

/*
public class FileEventTest {

	public static void main(String[] args) throws InterruptedException {
		Path pathToWatch = FileSystems.getDefault().getPath("/home/wus/tmp");
		DirectoryWatcher dirWatcher = new DirectoryWatcher(pathToWatch);
		Thread dirWatcherThread = new Thread(dirWatcher);
		dirWatcherThread.start();

		// interrupt the program after 10 seconds to stop it.
		Thread.sleep(10000); // 10000
		dirWatcherThread.interrupt();

	}
}
*/

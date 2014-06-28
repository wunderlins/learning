import java.applet.*;
import java.awt.*;

public class Label2 extends Applet {
    String text = "Hello!";
    int    x    = 50;
    int    y    = 25;

    private String getStrParam( String name, String defaultVal ) {
	String param = this.getParameter(name);
	if (param != null)   return param;
	return defaultVal;
    }

    private int getIntParam( String name, int defaultVal ) {
	String param = this.getParameter(name);
	if (param != null) {
	    try {
	        int i = Integer.parseInt( param );
		if (i > 0)   return i;
	    } catch (NumberFormatException e) {}
	}
	return defaultVal;
    }

    public void init() {
	super.init();
	text = getStrParam( "text",         text );
	x    = getIntParam( "x",            x    );
	y    = getIntParam( "y",            y    );
    }

    public void paint( Graphics g ) {
        g.drawString(  text, x, y );
    }
}

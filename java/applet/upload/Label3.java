import java.applet.*;
import java.awt.*;

public class Label3 extends Applet {
	String text = "Hello!";
	int x = 50;
	int y = 25;
	Color bg = new Color(0xCCCCCC);
	Color fg = new Color(0x000000);

	public String getAppletInfo() {
		return "Label3 1.0 example demo by Cynbe ru Taren: Public Domain";
	}

	public String[][] getParameterInfo() {
		String info[][] = {
				{ "foreground", "hexadecimal color value", "foreground color" },
				{ "background", "hexadecimal color value", "background color" },
				{ "x", "int", "x start for string" },
				{ "y", "int", "y start for string" },
				{ "text", "string", "text to display" } };
		return info;
	}

	private Color getClrParam(String name, Color defaultVal) {
		String param = this.getParameter(name);
		if (param != null) {
			try {
				int i = Integer.parseInt(param, 16);
				if (i > 0)
					return new Color(i);
			} catch (NumberFormatException e) {
			}
		}
		return defaultVal;
	}

	private String getStrParam(String name, String defaultVal) {
		String param = this.getParameter(name);
		if (param != null)
			return param;
		return defaultVal;
	}

	private int getIntParam(String name, int defaultVal) {
		String param = this.getParameter(name);
		if (param != null) {
			try {
				int i = Integer.parseInt(param);
				if (i > 0)
					return i;
			} catch (NumberFormatException e) {
			}
		}
		return defaultVal;
	}

	public void init() {
		super.init();
		text = getStrParam("text", text);
		x = getIntParam("x", x);
		y = getIntParam("y", y);
		bg = getClrParam("background", bg);
		fg = getClrParam("foreground", fg);
		this.setForeground(fg);
		this.setBackground(bg);
	}

	public void paint(Graphics g) {
		g.drawString(text, x, y);
	}
}

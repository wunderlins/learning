#!/usr/bin/env python

import wx

#wx = wx

class View(wx.Panel):
	def __init__(self, parent):
		super(View, self).__init__(parent)
		self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
		self.Bind(wx.EVT_SIZE, self.on_size)
		self.Bind(wx.EVT_PAINT, self.on_paint)
	
	def on_size(self, event):
		event.Skip()
		self.Refresh()
	
	def on_paint(self, event):
		w, h = self.GetClientSize()
		dc = wx.AutoBufferedPaintDC(self)
		dc.Clear()
		#dc.DrawLine(0, 0, w, h)
		dc.SetPen(wx.Pen('black', 1, wx.SOLID))
		
		#sky
		dc.SetBrush(wx.Brush('#004fc5'))
		dc.DrawRectangle(0, 0, w, h/2)
		
		#ground
		dc.SetBrush(wx.Brush('#539e47'))
		r2 = dc.DrawRectangle(0, h/2, w, h/2)
		
		#img = wx.Image("background.png", wx.BITMAP_TYPE_ANY)
		
		#dc.Rotate(50);
		
		#dc.SetPen(wx.Pen(wx.BLACK, 5))
		#dc.DrawCircle(w / 2, h / 2, 100)

class Frame(wx.Frame):
	def __init__(self):
		super(Frame, self).__init__(None)
		self.SetTitle('My Title')
		self.SetClientSize((500, 500))
		self.Center()
		self.view = View(self)

def main():
	app = wx.App(False)
	frame = Frame()
	frame.Show()
	app.MainLoop()

if __name__ == '__main__':
	main()

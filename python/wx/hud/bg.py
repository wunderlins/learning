#!/usr/bin/env python

import wx
 
class MyFrame(wx.Frame):
    def __init__(self, *args, **kw):
        wx.Frame.__init__(self, *args, **kw)
        
        self.bitmap = wx.Bitmap('chcross.png')
        self.image = self.bitmap.ConvertToImage()
        self.img_height = self.bitmap.GetHeight()
        self.img_width = self.bitmap.GetWidth()
        self.img_center = (self.img_height, self.img_width)
        print self.img_center
        
        wx.EVT_PAINT(self, self.OnPaint)
        self.Bind(wx.EVT_TIMER, self.OnTimer)
        self.counter = 0
 
        self.Centre()
        self.timer = wx.Timer(self)
        self.timer.Start(150)
 
    def OnPaint(self, event):
        self.dc = wx.PaintDC(self)
        self.dc.DrawBitmap(self.bitmap, 0, 0)
        
    def OnTimer(self, event):
        self.counter += .1
        img = self.image.Rotate(self.counter, self.img_center)
        img.Resize((self.img_height, self.img_width), wx.Point(50,50), r=-1, g=-1, b=-1)
        self.bitmap = img.ConvertToBitmap()
        self.dc.Clear()
        self.dc.DrawBitmap(self.bitmap, 100, 100)
        
 
app = wx.App(False)
frame = MyFrame(None, -1, "Rotate")
frame.SetSize(wx.Size(400, 400))
frame.Show(True)
app.MainLoop()
#!/usr/bin/env python

import wx

class View(wx.Panel):
    def __init__(self, parent):
        super(View, self).__init__(parent)
        self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
        self.Bind(wx.EVT_SIZE, self.on_size)
        self.Bind(wx.EVT_PAINT, self.on_paint)
        
        w, h = self.GetClientSize()
        self.w = w
        self.h = h
        
        self.roll = 0
        self.pitch = 0
        
        self.diag_deg = 0
    
    def on_size(self, event):
        w, h = self.GetClientSize()
        self.w = w
        self.h = h
        print "on_size: w %d, h %d" % (self.w, self.h)
        
        self.diag_deg()
        
        event.Skip()
        self.Refresh()
    
    def on_paint(self, event):
        self.hud_paint()
    
    def diag_deg(self):
        self.diag_deg = 0
        
    def attitude(self, roll, pitch):
        """
        roll, degrees. 
            0      = horizontal
            -180-0 = left
            0-180  = right
        
        pitch, degrees:
            0 
            -90-0 = down
            0-90  = up
            -90--180 = down inverted
            90-180   = up inverted
        """
        
        # roll implementation
        
        return True;
    
    def hud_paint(self):
        self.attitude(0, 0)
        
        dc = wx.AutoBufferedPaintDC(self)
        dc.Clear()
        #dc.DrawLine(0, 0, w, h)
        dc.SetPen(wx.Pen('black', 1, wx.SOLID))
        
        #sky
        dc.SetBrush(wx.Brush('#004fc5'))
        dc.DrawRectangle(0, 0, self.w, self.h/2)
        
        #ground
        dc.SetBrush(wx.Brush('#539e47'))
        r2 = dc.DrawRectangle(0, self.h/2, self.w, self.h/2)
        
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

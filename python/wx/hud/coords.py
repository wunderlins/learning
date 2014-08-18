#!/usr/bin/env python

import wx
import math

class View(wx.Panel):
    def __init__(self, parent):
        super(View, self).__init__(parent)
        self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
        self.Bind(wx.EVT_SIZE, self.on_size)
        self.Bind(wx.EVT_PAINT, self.on_paint)
        self.Bind(wx.EVT_TIMER, self.on_timer)
        
        w, h = self.GetClientSize()
        self.w = w
        self.h = h
        
        self.timer = wx.Timer(self)
        self.timer.Start(1000)
        
        
    def on_timer(self, event):
        print "on_timer"

    def on_size(self, event):
        w, h = self.GetClientSize()
        self.w = w
        self.h = h
        
        self.on_paint(event)
        
    def on_paint(self, event):
        dc = wx.AutoBufferedPaintDC(self)
        dc.Clear()
        #dc.DrawLine(0, 0, w, h)
        dc.SetPen(wx.Pen('black', 1, wx.SOLID))
        
        #sky
        dc.SetBrush(wx.Brush('#004fc5'))
        factor = 8
        w = self.w/factor
        h = self.h/factor
        dc.DrawRectangle(w*3, h*3, w*2, h*2)

class Frame(wx.Frame):
    def __init__(self):
        super(Frame, self).__init__(None)
        self.SetTitle('HUD')
        self.SetClientSize((500, 500))
        self.Center()
        self.view = View(self)

class calc():
    def angle_deg(self, adjacent, opposite):
        """ calculate the angle of a right triangle from oppsite and adjacent """
        #print "%f %f, at %f, factor %f" % (adjacent, opposite, math.atan(float(opposite)/float(adjacent)), (opposite/adjacent))
        return math.degrees(math.atan(float(opposite)/float(adjacent)));

def main():
    app = wx.App(False)
    frame = Frame()
    frame.Show()
    app.MainLoop()

if __name__ == '__main__':
    main()

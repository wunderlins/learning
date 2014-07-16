#!/usr/bin/env python

import wx
import math

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
        
        self.c = calc()
        self.diag_deg = 0.0
    
    def on_size(self, event):
        w, h = self.GetClientSize()
        self.w = w
        self.h = h
        
        self.diag_deg = self.c.angle_deg(w, h) 
        print "on_size: w %d, h %d, d %f" % (self.w, self.h, self.diag_deg)
        
        event.Skip()
        self.Refresh()
    
    def on_paint(self, event):
        self.hud_paint()
    
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

        # calculate hud ground and sky polygons
        # check if horizon crosses side or bottom/top window side
        if (roll > self.diag_deg or roll < self.diag_deg*-1):
            print "bottom/top"
            return (0, 0)
        
        else:
            # w2 = w/2
            # t = tan(roll)
            # t = opp/w2
            # w2 * t = opp
            # 
            y = (float(self.w)/2.0) * math.tan(math.radians(float(roll)))
            print "side, w: %f" % y
            
            # generate two points for an example line
            h2 = self.h/2.0
            p1 = (0, h2 + y)
            p2 = (self.w/2.0, h2)

            return (p1, p2);
    
    def hud_paint(self):
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
        
        att = self.attitude(30, 0)
        print att
        dc.DrawLine(att[0][0], att[0][1], att[1][0], att[1][1])
        
        
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

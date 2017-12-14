import os
import sys
import platform
from ctypes import *

class ctpdatawrapper:
    ctplib = None

    def __init__(self):
        ctplib = None

    def loadctpdll(self):
        sysstr = platform.system()
        dllpath = os.getcwd()
        if(sysstr =="Windows"):
            dllpath += "/ctpwrapper.dll"
        else:
            dllpath += "/libtomatotrade.so"
        print 'Try to load library'+dllpath
        self.ctplib = cdll.LoadLibrary(dllpath)

    def init_ctp_api(self, frantip, datapath):
        self.ctplib.init_ctp_api(frantip,datapath);
        
    def login_fdtc_md(self, brokerid, user, pwd, id):
        self.ctplib.login_fdtc_md(brokerid,user,pwd,id)

    def logout_fdtc_md(self, ppInstrumentID, nCount):
        self.ctplib.logout_fdtc_md(ppInstrumentID,nCount)

    def sub_market_data(self, ppInstrumentID, nCount):
        self.ctplib.sub_market_data(ppInstrumentID,nCount)

    def unsub_market_data(self, ppInstrumentID, nCount):
        self.ctplib.unsub_market_data(ppInstrumentID,nCount)

    def sub_for_quote_rsp(self,ppInstrumentID, nCount):
        self.ctplib.sub_for_quote_rsp(ppInstrumentID,nCount)

    def unsub_for_quote_rsp(self,ppInstrumentID, nCount):
        self.ctplib.unsub_for_quote_rsp(ppInstrumentID,nCount)

# for ctp wrapper test 
print 'CTP V1.0 START'
ctpw = ctpdatawrapper()
ctpw.loadctpdll()
print 'init ctp api address tcp://180.168.146.187:10000'
ctpw.init_ctp_api('tcp://180.168.146.187:10000','data')

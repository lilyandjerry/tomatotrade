import os
import sys
import platform
from ctypes import *


def on_front_connected():
    print "on_front_connected"
    pass

def on_front_disconnected(nReason):
    pass

def on_heart_beat_warning(nTimeLapse):
    pass

def on_rsp_user_login(pRspUserLogin, pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_user_logout(pUserLogout, pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_error(pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_sub_market_data(pSpecificInstrument, pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_unsub_market_data(pSpecificInstrument, pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_sub_for_quote_rsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast):
    pass

def on_rsp_unsub_for_quote_rsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast):
    pass

def on_rtn_depth_market_data(pDepthMarketData):
    pass

def on_rtn_for_quote_rsp(pForQuoteRsp):
    pass

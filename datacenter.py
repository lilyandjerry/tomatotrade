#! /usr/bin/python
import urllib
import httplib
import urllib2

class DataCenterSink:
    def On_Tick(self):
        pass


class DataCenter:
    def __init__(self):
        pass
    
    def get_hist_data(self, code):
        pass


url = "http://stock2.finance.sina.com.cn/futures/api/json.php/IndexService.getInnerFuturesMiniKLine5m?symbol=M0"
req = urllib2.Request(url)
print urllib2.urlopen(req).read()
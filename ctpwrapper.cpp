#include "ctpwrapper.h"
#include <stdio.h>
#include <string.h>

#include "CThostFtdcMdImp.h"

bool init_ctp_api(char* frantip,char* datapath){

    return CTHostFtdcMdImp::GetInstance()->InitMDImp(frantip,datapath);
}

int login_fdtc_md(char* brokerid, char* user, char* pwd, int id){
    
    return CTHostFtdcMdImp::GetInstance()->LoginFdtcMd(brokerid,user,pwd,id);
}

bool logout_fdtc_md(char* brokerid, char* user, char* pwd,int id){

    return CTHostFtdcMdImp::GetInstance()->LogoutFdtcMd(brokerid,user,pwd,id);
}

int sub_market_data(char *ppInstrumentID[], int nCount){

    return CTHostFtdcMdImp::GetInstance()->SubMarketData(ppInstrumentID,nCount);
}

int unsub_market_data(char *ppInstrumentID[], int nCount){

    return CTHostFtdcMdImp::GetInstance()->UnsubMarketData(ppInstrumentID,nCount);
}

int sub_for_quote_rsp(char *ppInstrumentID[], int nCount){

    return CTHostFtdcMdImp::GetInstance()->SubForQuoteRsp(ppInstrumentID,nCount);
}

int unsub_for_quote_rsp(char *ppInstrumentID[], int nCount){

    return CTHostFtdcMdImp::GetInstance()->UnsubForQuoteRsp(ppInstrumentID,nCount);
}
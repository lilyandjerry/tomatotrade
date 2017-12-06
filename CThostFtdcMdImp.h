#ifndef CC_THOST_FTDC_MD_IMP
#define CC_THOST_FTDC_MD_IMP

#include <stdio.h>
#include <string.h>

#include "ctpinterface/ThostFtdcMdApi.h"
#include "ctpinterface/ThostFtdcTraderApi.h"
#include "ctpinterface/ThostFtdcUserApiDataType.h"
#include "ctpinterface/ThostFtdcUserApiStruct.h"

class CTHostFtdcMdImp : public CThostFtdcMdSpi
{
public:
	CTHostFtdcMdImp();
	virtual ~CTHostFtdcMdImp();
	static CTHostFtdcMdImp* GetInstance();
	bool InitMDImp(char* frantip,char* datapath);
	bool DestoryMDImp();
	int LoginFdtcMd(char* brokerid, char* user, char* pwd, int id);
	bool LogoutFdtcMd(char* brokerid, char* user, char* pwd,int id);
	int SubMarketData(char *ppInstrumentID[], int nCount);
	int UnsubMarketData(char *ppInstrumentID[], int nCount);
	int SubForQuoteRsp(char *ppInstrumentID[], int nCount);
	int UnsubForQuoteRsp(char *ppInstrumentID[], int nCount);

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnHeartBeatWarning(int nTimeLapse);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
public:
	static CTHostFtdcMdImp* g_mdimp;
private:
	CThostFtdcMdApi* m_api;
};

#endif
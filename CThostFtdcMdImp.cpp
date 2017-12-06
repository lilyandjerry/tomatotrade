#include "CThostFtdcMdImp.h"


CTHostFtdcMdImp* CTHostFtdcMdImp::g_mdimp = NULL;
CTHostFtdcMdImp::CTHostFtdcMdImp(){
		m_api = NULL;
}

CTHostFtdcMdImp::~CTHostFtdcMdImp(){

}

CTHostFtdcMdImp* CTHostFtdcMdImp::GetInstance()
{
	if(NULL == CTHostFtdcMdImp::g_mdimp)
	{
		CTHostFtdcMdImp::g_mdimp = new CTHostFtdcMdImp();
	}
	
	return CTHostFtdcMdImp::g_mdimp;
}

bool CTHostFtdcMdImp::InitMDImp(char* frantip,char* datapath)
{
	m_api =	CThostFtdcMdApi::CreateFtdcMdApi(datapath, true);
	m_api->RegisterSpi(this);

	m_api->RegisterFront(frantip);
	m_api->Init();
	m_api->Join();
}

bool CTHostFtdcMdImp::DestoryMDImp()
{
	if(NULL == m_api)
		return true;
	return true;
}

int CTHostFtdcMdImp::LoginFdtcMd(char* brokerid, char* user, char* pwd, int id)
{
	if(NULL == m_api)
		return -1;

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerid);
	strcpy(req.UserID, user);
	strcpy(req.Password, pwd);
	int ret = m_api->ReqUserLogin(&req, id);
	return ret;
}

bool CTHostFtdcMdImp::LogoutFdtcMd(char* brokerid, char* user, char* pwd,int id)
{
	if(NULL == m_api)
		return false;

	CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerid);
	strcpy(req.UserID, user);
	int ret = m_api->ReqUserLogout(&req, id);
	return ret;
}

int CTHostFtdcMdImp::SubMarketData(char *ppInstrumentID[], int nCount)
{
	if(NULL == m_api)
		return -1;
	//char *ppInstrumentID[] = { "rb1801", "rm1801" };
	return m_api->SubscribeMarketData(ppInstrumentID, nCount);
}

int CTHostFtdcMdImp::UnsubMarketData(char *ppInstrumentID[], int nCount)
{
	if(NULL == m_api)
		return -1;

	return m_api->UnSubscribeMarketData(ppInstrumentID,nCount);
}

int CTHostFtdcMdImp::SubForQuoteRsp(char *ppInstrumentID[], int nCount)
{
	if(NULL == m_api)
		return -1;

	return m_api->SubscribeForQuoteRsp(ppInstrumentID,nCount);
}

int CTHostFtdcMdImp::UnsubForQuoteRsp(char *ppInstrumentID[], int nCount)
{
	if(NULL == m_api)
		return -1;
		
	return m_api->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}

void CTHostFtdcMdImp::OnFrontConnected() {

}

void CTHostFtdcMdImp::OnFrontDisconnected(int nReason) {

}

void CTHostFtdcMdImp::OnHeartBeatWarning(int nTimeLapse){


}

void CTHostFtdcMdImp::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

}

void CTHostFtdcMdImp::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData){

}

void CTHostFtdcMdImp::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp){

}
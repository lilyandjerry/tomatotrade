#include "CThostFtdcMdImp.h"
#include "python2.7/Python.h"

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
		printf("GetInstance new CTHostFtdcMdImp\n");
		CTHostFtdcMdImp::g_mdimp = new CTHostFtdcMdImp();
	}
	
	return CTHostFtdcMdImp::g_mdimp;
}

bool CTHostFtdcMdImp::InitLocalPython()
{
	printf("Init Python.\n");
	Py_Initialize(); 
    if ( !Py_IsInitialized() ) {
		printf("Init Python fail.");
        return false;  
    }

	printf("Init Python1.\n"); 
	PyRun_SimpleString("import sys");  
	printf("Init Python2.\n"); 
	PyRun_SimpleString("print '---import sys---'");
	printf("Init Python3.\n"); 
    PyRun_SimpleString("sys.path.append('./')");
	m_pName = PyString_FromString("ctpcallback"); 
	printf("Init Python1.\n"); 
    m_pModule = PyImport_Import(m_pName);  
    if ( !m_pModule ) {  
        printf("can't find ctpdatacenter.py");  
        getchar();  
        return false;  
	}

	m_pDict = PyModule_GetDict(m_pModule);
    if ( !m_pDict ){ 
		printf("can't get dict from ctpdatacenter.py");
        return false;  
	}
	printf("Init Python inited\n");
}

bool CTHostFtdcMdImp::InitMDImp(char* frantip,char* datapath)
{
	if(m_api)
		return true;

	printf("InitMDImp try CreateFtdcMdApi %s, frantip:%s\n", datapath,frantip);
	m_api =	CThostFtdcMdApi::CreateFtdcMdApi("data", true);
	printf("InitMDImp 1\n");
	if(!m_api)
	{
		printf("InitMDImp create api is error\n");
		return false;
	}
	printf("InitMDImp 2\n");
	m_api->RegisterSpi(this);
	printf("InitMDImp 3\n");
	m_api->RegisterFront(frantip);
	printf("InitMDImp 4\n");
	m_api->Init();
	printf("InitMDImp 5\n");
	int iRet = m_api->Join();
	printf("InitMDImp Join %s return is %d\n",frantip,iRet);
	return true;
}

bool CTHostFtdcMdImp::DestoryMDImp()
{
	Py_Finalize();
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

void CTHostFtdcMdImp::OnFrontConnected() 
{
	printf("CTHostFtdcMdImp::OnFrontConnected m_pModule %p\n",m_pModule);
	InitLocalPython();

	PyObject* pFunc = PyObject_GetAttrString(m_pModule, "on_front_connected");
	//PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_front_connected");
	printf("CTHostFtdcMdImp::OnFrontConnected pFunc\n");
	if ( !pFunc || !PyCallable_Check(pFunc) ) {  
       printf("can't find function [on_front_connected]");  
       getchar();  
       return;  
    }

	PyObject* pArgs;  
	pArgs = PyTuple_New(0);
	
	PyObject_CallObject(pFunc,NULL);
}

void CTHostFtdcMdImp::OnFrontDisconnected(int nReason) 
{
	InitLocalPython();

	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_front_disconnected");
}

void CTHostFtdcMdImp::OnHeartBeatWarning(int nTimeLapse)
{
	InitLocalPython();

	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_heart_beat_warning");
}

void CTHostFtdcMdImp::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_user_login");
}

void CTHostFtdcMdImp::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_user_logout");
}

void CTHostFtdcMdImp::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_error");
}

void CTHostFtdcMdImp::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_sub_market_data");
}

void CTHostFtdcMdImp::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_unsub_market_data");
}

void CTHostFtdcMdImp::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_sub_for_quote_rsp");
}

void CTHostFtdcMdImp::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rsp_unsub_for_quote_rsp");
}

void CTHostFtdcMdImp::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rtn_depth_market_data");
}

void CTHostFtdcMdImp::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	InitLocalPython();
	PyObject* pFunc = PyDict_GetItemString(m_pDict, "on_rtn_for_quote_rsp");
}
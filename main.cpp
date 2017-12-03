#include <stdio.h>
#include <string.h>

#include "ctpinterface\ThostFtdcMdApi.h"
#include "ctpinterface\ThostFtdcTraderApi.h"
#include "ctpinterface\ThostFtdcUserApiDataType.h"
#include "ctpinterface\ThostFtdcUserApiStruct.h"

class MarketDataCollector : public CThostFtdcMdSpi
{
public:
	MarketDataCollector(CThostFtdcMdApi* api)
	{
		m_api = api;
	}

	virtual ~MarketDataCollector()
	{}

public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected() {
		int requestId = 1;
		CThostFtdcReqUserLoginField req;
		memset(&req, 0, sizeof(req));
		strcpy(req.BrokerID, "***");
		strcpy(req.UserID, "****");
		strcpy(req.Password, "***");
		int ret = m_api->ReqUserLogin(&req, ++requestId);
	};

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason) {};

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse) {};


	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		char *ppInstrumentID[] = { "rb1801", "rm1801" };
		int ret = m_api->SubscribeMarketData(ppInstrumentID, 2);
	};

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ѯ��Ӧ��
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};
private:
	CThostFtdcMdApi* m_api;
};

int main()
{
	CThostFtdcMdApi *api =	CThostFtdcMdApi::CreateFtdcMdApi("data", true);
	
	MarketDataCollector mdCollector(api);
	api->RegisterSpi(&mdCollector);

	api->RegisterFront("tcp://180.168.146.187:10000");
	api->Init();
	api->Join();
    return true;
}

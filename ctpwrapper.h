#ifndef CC_CTP_WRAPPER_HH
#define CC_CTP_WRAPPER_HH

#ifdef __cplusplus
extern "C" {
#endif

bool init_ctp_api(char* frantip,char* datapath);
int login_fdtc_md(char* brokerid, char* user, char* pwd, int id);
bool logout_fdtc_md(char* brokerid, char* user, char* pwd,int id);
int sub_market_data(char *ppInstrumentID[], int nCount);
int unsub_market_data(char *ppInstrumentID[], int nCount);
int sub_for_quote_rsp(char *ppInstrumentID[], int nCount);
int unsub_for_quote_rsp(char *ppInstrumentID[], int nCount);

#ifdef __cplusplus
}
#endif

#endif
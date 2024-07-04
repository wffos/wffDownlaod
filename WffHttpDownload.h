#ifndef _WFF_HTTP_DOWHLAOD_H_
#define _WFF_HTTP_DOWHLAOD_H_

#include "IWffDownlaod.h"
#include <curl/curl.h>

struct HttpFile
{
    std::string filename;
    FILE *stream;
};
class CWffHttpDownload : public IWffDownlaod
{
private:
    /* data */
public:
    CWffHttpDownload(/* args */);
    virtual ~CWffHttpDownload();

    virtual bool SatrtDownlaod(const char *const szURL, const char *const szLocalFile, bool bSSL);

private:
    CURL *ResetCurl();
    void ReleasaCurl();

private:
    CURL *m_pCurl;
    string m_strLastError;
};

#endif
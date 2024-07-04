#ifndef _WFF_DOWHLAOD_H_
#define _WFF_DOWHLAOD_H_

#include "IWffDownlaod.h"

#include <string>
using namespace std;

enum DownloadMode
{
    DOWNLOAD_MODE_HTTP = 1,
    DOWNLOAD_MODE_FTP
};

class CWffDownload
{
public:
    CWffDownload() { m_downloadMode = DOWNLOAD_MODE_HTTP; };
    virtual ~CWffDownload(){};

    void SetDownloadMode(DownloadMode &downloadMode);

    void SetDownloadParam(const string &strUrl, const string &strLocalFile);

    virtual void StartDownload();

private:
    DownloadMode m_downloadMode;
    string m_strUrl;
    string m_strLocalFile;
};

#endif
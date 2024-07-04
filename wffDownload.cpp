#include "wffDownload.h"
#include "IWffDownlaod.h"
#include "WffHttpDownload.h"

void CWffDownload::SetDownloadMode(DownloadMode &downloadMode)
{
    m_downloadMode = downloadMode;
};

void CWffDownload::SetDownloadParam(const string &strUrl, const string &strLocalFile)
{
    m_strUrl = strUrl;
    m_strLocalFile = strLocalFile;
};

void CWffDownload::StartDownload()
{
    if (m_downloadMode == DOWNLOAD_MODE_HTTP)
    {
        if (true) // todo : check args
        {
            IWffDownlaod *pwffDownload = new CWffHttpDownload;
            if (pwffDownload != nullptr)
            {
                pwffDownload->SatrtDownlaod(m_strUrl.c_str(), m_strLocalFile.c_str(), false);
                delete pwffDownload;
                pwffDownload = nullptr;
            }
        }
    }
    else
    {
        // todo : ftp download
    }
};
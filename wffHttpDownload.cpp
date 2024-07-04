#include "WffHttpDownload.h"

CWffHttpDownload::CWffHttpDownload(/* args */)
{
}

CWffHttpDownload::~CWffHttpDownload()
{
}

CURL *CWffHttpDownload::ResetCurl()
{
    if (!m_pCurl)
    {
        curl_easy_cleanup(m_pCurl);
    }

    m_pCurl = curl_easy_init();
    return m_pCurl;
}

void CWffHttpDownload::ReleasaCurl()
{
    if (!m_pCurl)
    {
        curl_easy_cleanup(m_pCurl);
        m_pCurl = NULL;
    }
}

static size_t DownloadfileCallback(void *buffer, size_t size, size_t nmemb, void *stream)
{
    HttpFile *out = (struct HttpFile *)stream;
    if (out && !out->stream)
    {
        out->stream = fopen(out->filename.c_str(), "wb+");
        if (!out->stream)
            return -1; /* failure, can‘t open file to write */
    }
    FILE *localFile = out->stream;
    size_t sizeWritten = fwrite(buffer, size, nmemb, localFile);
    // fclose(hHandle);
    // FILE* recordFile = fopen("WffDownload.conf", "ab+");
    // fwrite(buffer, size, nmemb, localFile);

    return sizeWritten;
}

bool CWffHttpDownload::SatrtDownlaod(const char *const szURL, const char *const szLocalFile, bool bSSL)
{
    CURL *curl = ResetCurl();
    CURLcode code = CURL_LAST;
    HttpFile httpfile;

    if (curl == NULL)
    {
        m_strLastError = "Curl Initialization Failure!";
        return false;
    }

    httpfile.filename = szLocalFile;
    httpfile.stream = NULL;
    try
    {
        struct curl_slist *headers = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, szURL);
        if (bSSL)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // https
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // verify false
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadfileCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpfile);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50); //
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5);   //
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 250L);

        code = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        if (code != CURLE_OK)
        {
            m_strLastError = "CCurlHttpSsl Download Error : " + to_string(code);
            // delete local file
        }
        if (httpfile.stream)
        {
            fclose(httpfile.stream);
        }
    }
    catch (...)
    {
        m_strLastError = "CCurlHttpSsl Download Unknow Error";
    }
    return code == CURLE_OK ? true : false;
}
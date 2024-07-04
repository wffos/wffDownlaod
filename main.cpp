#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>

#include "wffDownload.h"

using namespace std;

#define MAX_THREAD_COUNT 20

bool SplitString(string strRaw, char szDev, vector<string> &vData)
{
    if (strRaw.at(strRaw.length() - 1) != '|')
    {
        strRaw = strRaw + "|";
    }

    for (auto i = strRaw.find(szDev); i != string::npos; i = strRaw.find(szDev))
    {
        string strData = strRaw.substr(0, i);
        strRaw = strRaw.substr(i + 1);
        vData.push_back(strData);
    }

    return true;
}

int main(int argc, char *argv[])
{
    string strUrl;// = "http://192.168.2.152:80/download/1.txt|http://192.168.2.152:80/download/2.txt";
    string strDir;// = "/home/wff/Desktop";

    int arg;
    while ((arg = getopt(argc, argv, "u:d:h")) != EOF)
    {
        switch (arg)
        {
        case 'u':
        {
            strUrl = optarg;
            cout << "download url : " << optarg << endl;
            break;
        }
        case 'd':
        {
            strDir = optarg;
            cout << "save file to : " << optarg << endl;
            break;
        }
        case 'h':
        {
            strUrl = "";
            strDir = "";
            break;
        }
        }
    }

    if (strUrl.length() == 0 || strDir.length() == 0)
    {
        cout << "useage : ./wffDownload -u \"http://192.168.2.152:80/download/1.txt|http://192.168.2.152:80/download/2.txt\" -d /home/wff/Desktop" << endl;
        exit(-1);
    }

    vector<string> vUrls;
    SplitString(strUrl, '|', vUrls);
    vector<thread> threadPoll;
    vector<CWffDownload *> vDownloader;
    for (auto &url : vUrls)
    {
        CWffDownload *pwffDownloader = new CWffDownload;
        pwffDownloader->SetDownloadParam(url, strDir + url.substr(url.find_last_of('/')));
        threadPoll.push_back(thread(&CWffDownload::StartDownload, pwffDownloader));
        vDownloader.push_back(pwffDownloader);
    }
    for (auto &threadPos : threadPoll)
    {
        threadPos.join();
    }
    for (auto &downloader : vDownloader)
    {
        delete downloader;
    }

    return 0;
}

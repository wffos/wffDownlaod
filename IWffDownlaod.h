#ifndef _WFF_DOWNLAOD_INTERFACE_H_
#define _WFF_DOWNLAOD_INTERFACE_H_

#include <string>
using namespace std;

class IWffDownlaod
{
public:
    IWffDownlaod(){};
    virtual ~IWffDownlaod(){};
    virtual bool SatrtDownlaod(const char *const szURL, const char *const szLocalFile, bool bSSL) { return true; };
};

#endif
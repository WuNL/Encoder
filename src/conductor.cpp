//
// Created by sdt on 18-8-6.
//

#include <include/conductor.h>
#include <cstring>

const initParamsRet conductor::initEncoder(initParams& p)
{
    initParamsRet ret;
    memset(&ret,0x00,sizeof(initParamsRet));

    if(findEncoderByName(p.encoder_name)!=-1)
    {

        ret.success=false;
        return ret;
    }
    else
    {
        std::unique_ptr<encoder> e
    }

    return ret;
}

int conductor::findEncoderByName(std::string& name)
{
    for(int i =0;i<encoderVec.size();++i)
    {
        if(encoderVec[i]->getName()==name)
            return i;
    }
    return -1;
}

//
// Created by sdt on 18-8-8.
//

#ifndef ENCODER_JSONPARSER_H
#define ENCODER_JSONPARSER_H

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "encoder.h"

using namespace boost::property_tree;

int jsonParser (std::string &rawJson, initParams &params)
{
    ptree pt;                       //define property_tree object
    std::stringstream ss(rawJson);
    try
    {
        read_json(ss, pt);          //parse json
    } catch (ptree_error &e)
    {
        return 1;
    }
    try
    {
        params.encoder_name = pt.get<std::string>("encoder_name");
        params.codec = pt.get<std::string>("codec");
        params.v_width = pt.get<int>("v_width");
        params.v_height = pt.get<int>("v_height");
        params.v_gop = pt.get<int>("v_gop");
        params.packetMode = pt.get<int>("packetMode");
        params.framerate = 30;
        params.bitrate = 1000;
    }
    catch (...)
    {
        return 1;
    }


}

#endif //ENCODER_JSONPARSER_H

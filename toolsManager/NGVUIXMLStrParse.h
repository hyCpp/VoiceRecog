/**
 * Copyright @ 2014 - 2016 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file NGVUIXMLStrParse.h
 * @brief Declaration file of class NGVUIXMLStrParse.
 *
 * This file includes the declaration of class NGVUIXMLStrParse, and
 * the definitions of the parse XML.
 *
 * @attention used for C++ only.
 */
#ifndef NGVUIXMLSTRPARSE
#define NGVUIXMLSTRPARSE

#include "pugixml.hpp"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::string> XmlMap;
typedef std::vector<XmlMap> XmlVectorMap;
typedef std::vector<std::string> XmlVector;

#ifndef __cplusplus
#    error ERROR: this file requires C++ compilation (use a .cpp suffic)
#endif

/**
 * Summary description.
 *
 * Details description of the class.
 *
 */

class NGVUIXMLStrParse
{
public:
    NGVUIXMLStrParse(const std::string & xmlStr);
    ~NGVUIXMLStrParse();

    /**
     * function of GetXMLValue.
     *
     * @param tag is xml node name; attributeName is xml node attribute name
     *
     * @return string.
     *
     * @Description : Output attribute values based on nodes and attributes,
     *              According to the node name output node value
     */
    std::string GetXMLValue(const std::string &tag, const std::string& attributeName = "") const;

    /**
     * function of GetXMLListValue.
     *
     * @param nodePath is xml node path; eg : //action/params
     *
     * @return std::vector<<std::map<std::string, std::string> >.
     *
     * @Description : Convert XML to map
     */
    XmlVectorMap GetXMLListValue(const std::string& nodePath) const;

    /**
     * function of GetXMLListNodeValue.
     *
     * @param nodePath is xml node path; eg : //action/params
     *
     * @return std::vector<std::string>.
     *
     * @Description : Convert XML to vector
     */
    XmlVector GetXMLListNodeValue(const std::string& nodePath) const;

    /**
     * function of makeQueryXml.
     *
     * @param nodePath is node path, content is node value
     *
     * @return std::string
     *
     * @Description : set node value and return string
     */
    std::string makeQueryXml(const std::string& nodePath, const std::string& content);

    /**
     * function of makeQueryXml.
     *
     * @param nodePath is node path, nodeName is node name, content is node value
     *
     * @return std::string
     *
     * @Description : create node and set node value;
     */
    std::string makeQueryXml(const std::string& nodePath, const std::string& nodeName, const std::string& content);
    std::string fixXMLNode(const std::string& nodePath, const std::string& content);

    std::string setXMLAttr(const std::string& nodePath, const std::string& attr, const std::string& content);

private:
    void setXmlNode(pugi::xml_node node, const std::string& content);
    void setXmlNode(pugi::xpath_node_set nodes, const std::string& content);
    void setXmlNode(pugi::xml_node node, const std::string& xpath, const std::string& content);
    std::string transferXmlToString(pugi::xml_node node);

private:
    pugi::xml_document m_dom;
};

#endif // NGVUIXMLSTRPARSE
/* EOF */

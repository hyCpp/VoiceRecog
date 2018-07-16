/**
 * Copyright @ 2014 - 2017 Suntec Software(Shanghai) Co., Ltd.
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

#include "NGVUIXMLStrParse.h"
#include <memory.h>
#include "config.h"
#include <sstream>
#include "pugiconfig.hpp"
#include "pugixml.cpp"

NGVUIXMLStrParse::NGVUIXMLStrParse(const std::string & xmlStr)
{
    if (!m_dom.load_string(xmlStr.c_str())) {
        TCLOGD("m_dom.load_string(xmlStr.c_str()) is fail !");
        return;
    }
}

NGVUIXMLStrParse::~NGVUIXMLStrParse()
{
}

std::string NGVUIXMLStrParse::GetXMLValue(const std::string &tag, const std::string &attributeName) const
{
    std::string result = "";
    pugi::xml_node nodelist = m_dom.select_node(("//" + tag).c_str()).node();

    if (attributeName.compare("") == 0) {
        if (nodelist.empty()) {
            TCLOGD("Parse Exception! -- node = [%s]", tag.c_str());
        }
        else {
            result = nodelist.text().as_string();
        }
    }
    else {
        if (nodelist.attribute(attributeName.c_str()).empty()) {
            TCLOGD("Parse Exception! -- node = [%s], attributeName = [%s]", tag.c_str(), attributeName.c_str());
        }
        else {
            result = nodelist.attribute(attributeName.c_str()).value();
        }
    }

    return result;
}

XmlVectorMap NGVUIXMLStrParse::GetXMLListValue(const std::string& nodePath) const
{
    pugi::xpath_node_set nodelist = m_dom.select_nodes(nodePath.c_str());
    XmlVectorMap xmlList;
    XmlMap result;

    if (!nodelist.empty()) {
        for (pugi::xpath_node_set::const_iterator it = nodelist.begin(); it != nodelist.end(); ++it) {
            pugi::xpath_node node = *it;
            pugi::xml_node itemList = node.node();

            if (!itemList.empty()) {

                for (pugi::xml_node::iterator iter = itemList.begin(); iter != itemList.end(); ++iter) {
                    result[(*iter).name()] = (*iter).text().get();
                }

                xmlList.push_back(result);
                result.clear();
            }
        }
    }
    else {
        TCLOGD("Parse Exception! -- nodelist is empty!");
    }

    return xmlList;
}

XmlVector NGVUIXMLStrParse::GetXMLListNodeValue(const std::string &nodePath) const
{
    pugi::xpath_node_set nodelist = m_dom.select_nodes(nodePath.c_str());
    XmlVector xmlList;

    if (!nodelist.empty()) {
        for (pugi::xpath_node_set::const_iterator it = nodelist.begin(); it !=  nodelist.end(); ++it) {
            pugi::xpath_node node = *it;
            pugi::xml_node itemList = node.node();
            xmlList.push_back(itemList.text().as_string());
        }
    }
    else {
        printf("Parse Exception! -- nodelist is empty!\n");
    }

    return xmlList;
}

std::string NGVUIXMLStrParse::makeQueryXml(const std::string& nodePath, const std::string& content)
{
    setXmlNode(m_dom, nodePath, content);

    return transferXmlToString(m_dom);
}

std::string NGVUIXMLStrParse::makeQueryXml(const std::string &nodePath, const std::string &nodeName, const std::string &content)
{
    pugi::xml_node appendNode = m_dom.select_node(("//" + nodePath).c_str()).node();

    if (appendNode.empty()) {
        TCLOGD("Parse Exception! -- nodePath = [%s], is not exist!", nodePath.c_str());
    }
    else {
        if (nodeName.compare("") != 0) {
            appendNode.append_child(nodeName.c_str()).append_child(pugi::node_pcdata).set_value(content.c_str());
        }
        else {
            TCLOGD("Parse Exception! -- nodeName = [%s], is not exist!", nodeName.c_str());
        }
    }

    return transferXmlToString(m_dom);
}

void NGVUIXMLStrParse::setXmlNode(pugi::xml_node node, const std::string& content)
{
    pugi::xml_node textNode = node.append_child(pugi::xml_node_type::node_pcdata);
    textNode.text() = content.c_str();
}

void NGVUIXMLStrParse::setXmlNode(pugi::xpath_node_set nodes, const std::string& content)
{
    for (auto xnode : nodes) {
        setXmlNode(xnode.node(), content);
    }
}

void NGVUIXMLStrParse::setXmlNode(pugi::xml_node node, const std::string& xpath, const std::string& content)
{
    pugi::xpath_node_set nodes = node.select_nodes(xpath.c_str());
    setXmlNode(nodes, content);
}

std::string NGVUIXMLStrParse::fixXMLNode(const std::string &nodePath, const std::string &content)
{
    pugi::xml_node textNode = m_dom.select_node(nodePath.c_str()).node();
    textNode.text() = content.c_str();

    return transferXmlToString(m_dom);
}

std::string NGVUIXMLStrParse::setXMLAttr(const std::string &nodePath, const std::string &attr, const std::string &content)
{
    pugi::xpath_node xnode = m_dom.select_node(nodePath.c_str());
    if (!xnode) {
        TCLOGD("set xml attr error!");
        return "";
    }

    pugi::xml_attribute xattr = xnode.node().append_attribute(attr.c_str());
    if (!xattr) {
        TCLOGD("set xml attr error!");
        return "";
    }

    bool res = xattr.set_value(content.c_str());
    if (!res) {
        TCLOGD("set xml attr error");
    }
    return transferXmlToString(m_dom);
}

std::string NGVUIXMLStrParse::transferXmlToString(pugi::xml_node node)
{
    std::stringstream ss;
    node.print(ss);
    return ss.str();
}

/* EOF */
